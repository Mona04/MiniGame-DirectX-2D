#include "Framework.h"
#include "FontImporter.h"

#include "Framework/Scene/Component/Transform.h"
#include "Framework/Scene/Component/Renderable.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#define GLYPH_ROMAN_START 0x0000
#define GLYPH_ROMAN_END 0x007E
#define GLYPH_KOREAN_START 0xAC00
#define GLYPH_KOREAN_END 0xD7AF

#define ATLAS_MAX_WIDTH 1024
#define ATLAS_VERTICAL_OFFSET 3
#define ATLAS_HORIZONTAL_OFFSET 3

#define UNICODE_TAB 0x09
#define UNICODE_NEW_LINE 0x0a
#define UNICODE_SPACE 0x20

FT_Library ft_library;
FT_UInt32 charFlags = FT_LOAD_DEFAULT | FT_LOAD_RENDER;

FontImporter::FontImporter(Context* context)
	: context(context)
{
	if (FT_Init_FreeType(&ft_library))
		LOG_ERROR("Failed to initialize");

	FT_Int major, minor, revision;
	FT_Library_Version(ft_library, &major, &minor, &revision);

	resourceManager = context->GetSubsystem<ResourceManager>();
}

FontImporter::~FontImporter()
{
	FT_Done_FreeType(ft_library);
}

const bool FontImporter::LoadFromFile(Glyphs& glyphs)
{
	charFlags |= glyphs.isForceAutoHint ? FT_LOAD_FORCE_AUTOHINT : 0;
	switch (glyphs.hintingType)
	{
	case HintingType::None:
		charFlags |= FT_LOAD_NO_HINTING;
		break;
	case HintingType::Light:
		charFlags |= FT_LOAD_TARGET_LIGHT;
		break;
	case HintingType::Normal:
		charFlags |= FT_LOAD_TARGET_NORMAL;
		break;
	}

	//Create Face
	FT_Face face;
	if (ErrorHandler(FT_New_Face(ft_library, glyphs.path.c_str(), 0, &face)))
	{
		FT_Done_Face(face);
		return false;
	}

	if (ErrorHandler(FT_Set_Char_Size(face, 0, glyphs.fontSize * 64, 96, 96))) // width, height is 1/64th of points
	{
		FT_Done_Face(face);
		return false;
	}

	//Compute Atlas Dimension
	uint atlasWidth = 0;
	uint atlasHeight = 0;
	uint rowHeight = 0;
	ComputeAtlasTextureDimension(face, atlasWidth, atlasHeight, rowHeight);

	//Make Buffer for Mesh
	std::vector<std::byte> atlasBuffer;
	atlasBuffer.reserve(atlasWidth * atlasHeight * 4);
	atlasBuffer.resize(atlasWidth * atlasHeight * 4);

	uint penX = 0;
	uint penY = 0;
	uint i = GLYPH_ROMAN_START - 1;
	while(true)
	{
		i++;
		if (i == GLYPH_ROMAN_END + 1)
			i = GLYPH_KOREAN_START;
		if (i == GLYPH_KOREAN_END + 1)
			break;

		//문제 있으면 건너뛰기
		if (ErrorHandler(FT_Load_Char(face, i, charFlags)))
			continue;

		FT_Bitmap* bitmap = &face->glyph->bitmap;
		
		for (uint y = 0; y < bitmap->rows; y++)
		{
			for (uint x = 0; x < bitmap->width; x++)
			{
				uint _x = penX + x;
				uint _y = penY + y;
				uint atlasPos = _x + _y * atlasWidth;
				//assert(atlasBuffer.size() > atlasPos);

				switch (bitmap->pixel_mode)
				{
				case FT_PIXEL_MODE_MONO:
					// Todo//
					break;
				case FT_PIXEL_MODE_GRAY:
					atlasBuffer[atlasPos*4 + 0] = static_cast<std::byte>(bitmap->buffer[x + y * bitmap->width]);
					atlasBuffer[atlasPos*4 + 1] = atlasBuffer[atlasPos * 4 + 0];
					atlasBuffer[atlasPos*4 + 2] = atlasBuffer[atlasPos * 4 + 0];
					atlasBuffer[atlasPos*4 + 3] = atlasBuffer[atlasPos * 4 + 0];
					break;
				case FT_PIXEL_MODE_BGRA:
					//Todo//
					break;
				default:
					LOG_ERROR("Font uses unsupported pixel format");
					break;
				}
			}
		}
		atlasBuffer.shrink_to_fit();

		Glyph glyph;
		glyph.left = penX;
		glyph.top = penY;
		glyph.right = penX + bitmap->width;
		glyph.bottom = penY + bitmap->rows;
		glyph.width = glyph.right - glyph.left;
		glyph.height = glyph.bottom - glyph.top;
		glyph.uv_left = (float)glyph.left / (float)atlasWidth;
		glyph.uv_right = (float)glyph.right / (float)atlasWidth;
		glyph.uv_top = (float)glyph.top / (float)atlasHeight;
		glyph.uv_bottom = (float)glyph.bottom / (float)atlasHeight;
		glyph.descent = rowHeight - face->glyph->bitmap_top;
		glyph.space_offset = face->glyph->advance.x >> 6;

		if (i >= 1 && FT_HAS_KERNING(face))
		{
			FT_Vector kerningVec;
			FT_Get_Kerning(face, i - 1, i, FT_KERNING_DEFAULT, &kerningVec);
			glyph.space_offset += kerningVec.x >> 6;
		}
		glyph.space_offset += face->glyph->metrics.horiBearingX;

		glyphs.glyphs[i] = glyph;

		penX += bitmap->width + ATLAS_HORIZONTAL_OFFSET;

		if (penX >= atlasWidth)
		{
			penX = bitmap->width + ATLAS_HORIZONTAL_OFFSET;
			penY += rowHeight + ATLAS_VERTICAL_OFFSET;
		}
	}
	FT_Done_Face(face);
	
	glyphs.maxHeight = 0;
	glyphs.maxWidth = 0;
	for (const auto& glyph : glyphs.glyphs)
	{
		glyphs.maxWidth = Math::Max<uint>(glyph.second.width, glyphs.maxWidth);
		glyphs.maxHeight = Math::Max<uint>(glyph.second.height, glyphs.maxHeight);
	}

	//Create Texture
	Texture* textureAtlas = resourceManager->Load<Texture>(NULL_STRING, glyphs.name);
	textureAtlas->SetBPP(8);
	textureAtlas->SetBPC(8);
	textureAtlas->SetWidth(atlasWidth);
	textureAtlas->SetHeight(atlasHeight);
	textureAtlas->SetChannel(4);
	textureAtlas->SetTransparent(true);
	textureAtlas->SetFormat(DXGI_FORMAT_R8G8B8A8_UNORM);
	textureAtlas->SetGrayScaled(true);
	if (!textureAtlas->CreateShaderResourseView(atlasWidth, atlasHeight, 4, DXGI_FORMAT_R8G8B8A8_UNORM, atlasBuffer))
	{
		LOG_ERROR("Failed to create shader resource.");
		return false;
	}

	glyphsMap[glyphs.name] = glyphs;

	return true;
}

const bool FontImporter::SetText(const std::string& glyphsName, const std::wstring& text, class Renderable* renderable, Transform* transform)
{
	if (!renderable || !transform)
		return false;

	Vector2 pen = Vector2(transform->GetPosition().x, transform->GetPosition().y);
	Mesh* mesh = renderable->GetMesh();
	Material* material = renderable->GetMaterial();
	Geometry<VertexTextureNormal>& geometry = mesh->GetGeometry();
	geometry.Clear();

	Glyphs glyphs = glyphsMap[glyphsName];

	for (const wchar_t& textChar : text)
	{
		Glyph glyph = glyphs.glyphs[textChar];

		if (textChar == UNICODE_TAB)
		{
			int space_offset = glyphs.glyphs[UNICODE_SPACE].space_offset;
			int space_count = 8;
			int tab_spacing = space_offset * space_count;
			int column_header = int(pen.x - transform->GetPosition().x);
			int offset_to_next_tab_stop = tab_spacing - (column_header % (tab_spacing != 0 ? tab_spacing : 1));
			pen.x += offset_to_next_tab_stop;
			continue;
		}

		if (textChar == UNICODE_NEW_LINE)
		{
			pen.y = pen.y - glyphs.maxHeight;
			pen.x = transform->GetPosition().x;
			continue;
		}

		if (textChar == UNICODE_SPACE)
		{
			pen.x += glyph.space_offset;
			continue;
		}

		geometry.AddVertex(VertexTextureNormal(Vector3(pen.x, (pen.y - glyph.height - glyph.descent), 0.0f) / 100.0f, Vector2(glyph.uv_left, glyph.uv_bottom), Vector3(0.0f, 0.0f, 0.0f)));	// Bottom left
		geometry.AddVertex(VertexTextureNormal(Vector3(pen.x, pen.y - glyph.descent, 0.0f) / 100.0f, Vector2(glyph.uv_left, glyph.uv_top), Vector3(0.0f, 0.0f, 0.0f)));		// Top left
		geometry.AddVertex(VertexTextureNormal(Vector3((pen.x + glyph.width), (pen.y - glyph.height - glyph.descent), 0.0f) / 100.0f, Vector2(glyph.uv_right, glyph.uv_bottom), Vector3(0.0f, 0.0f, 0.0f)));	// Bottom right
		geometry.AddVertex(VertexTextureNormal(Vector3((pen.x + glyph.width), (pen.y - glyph.height - glyph.descent), 0.0f) / 100.0f, Vector2(glyph.uv_right, glyph.uv_bottom), Vector3(0.0f, 0.0f, 0.0f)));	// Bottom right
		geometry.AddVertex(VertexTextureNormal(Vector3(pen.x, pen.y - glyph.descent, 0.0f) / 100.0f, Vector2(glyph.uv_left, glyph.uv_top), Vector3(0.0f, 0.0f, 0.0f)));		// Top left
		geometry.AddVertex(VertexTextureNormal(Vector3((pen.x + glyph.width), pen.y - glyph.descent, 0.0f) / 100.0f, Vector2(glyph.uv_right, glyph.uv_top), Vector3(0.0f, 0.0f, 0.0f)));	// Top right

		pen.x = pen.x + glyph.width;
	}

	for (uint i = 0; i < geometry.GetVertexCount(); i++)
		geometry.AddIndex(i);

	VertexBuffer* vertexBuffer = mesh->GetVertexBuffer();
	IndexBuffer* indexBuffer = mesh->GetIndexBuffer();

	if (geometry.GetVertexCount() > vertexBuffer->GetVertexCount())
	{
		vertexBuffer->Clear();
		vertexBuffer->Create(geometry.GetVertices(), D3D11_USAGE_DYNAMIC);

		indexBuffer->Clear();
		indexBuffer->Create(geometry.GetIndices(), D3D11_USAGE_DYNAMIC);
	}

	auto vdata = vertexBuffer->Map<VertexTextureNormal>();
	{
		memcpy(vdata, geometry.GetVertexData(), geometry.GetVertexCount() * sizeof(VertexTextureNormal));
		vertexBuffer->SetVertexCount(geometry.GetVertexCount());
	}
	vertexBuffer->Unmap();

	auto idata = indexBuffer->Map();
	{
		memcpy(idata, geometry.GetIndexData(), geometry.GetIndexCount() * sizeof(uint));
		indexBuffer->SetIndexCount(geometry.GetIndexCount());
	}
	indexBuffer->Unmap();
}

void FontImporter::ComputeAtlasTextureDimension(FT_FaceRec_* face, uint& atlasWidth, uint& atlasHeight, uint& rowHeight)
{
	int penX = 0;
	atlasWidth = ATLAS_MAX_WIDTH;
	rowHeight = GetCharacterMaxHeight(face);
	atlasHeight = rowHeight;

	uint i = GLYPH_ROMAN_START - 1;
	while(true)
	{
		i++;
		if (i == GLYPH_ROMAN_END + 1)
			i = GLYPH_KOREAN_START;
		if (i == GLYPH_KOREAN_END + 1)
			break;
		if (ErrorHandler(FT_Load_Char(face, i, FT_LOAD_RENDER | FT_LOAD_TARGET_LIGHT)))
			continue;

		FT_Bitmap* bitmap = &face->glyph->bitmap;

		penX += bitmap->width + ATLAS_HORIZONTAL_OFFSET;

		if (penX >= ATLAS_MAX_WIDTH)
		{
			penX = bitmap->width + ATLAS_HORIZONTAL_OFFSET;
			atlasHeight += rowHeight + ATLAS_VERTICAL_OFFSET;
		}
	}
}

const int FontImporter::GetCharacterMaxHeight(FT_FaceRec_* face)
{
	int max_height = 0;
	uint i = GLYPH_ROMAN_START - 1;
	while (true)
	{
		i++;
		if (i == GLYPH_ROMAN_END + 1)
			i = GLYPH_KOREAN_START;
		if (i == GLYPH_KOREAN_END + 1)
			break;
		if (ErrorHandler(FT_Load_Char(face, i, FT_LOAD_RENDER)))
			continue;

		FT_Bitmap* bitmap = &face->glyph->bitmap;
		max_height = Math::Max<uint>(max_height, bitmap->rows);
	}

	return max_height;
}

const bool FontImporter::ErrorHandler(const int& errorCode)
{
	if (errorCode == FT_Err_Ok)
		return false;

	switch (errorCode)
	{
		// Generic errors
	case FT_Err_Cannot_Open_Resource:	        LOG_ERROR("FreeType: Cannot open resource.")                        break;
	case FT_Err_Unknown_File_Format:	        LOG_ERROR("FreeType: Unknown file format.");                        break;
	case FT_Err_Invalid_File_Format:	        LOG_ERROR("FreeType: Broken file.");                                break;
	case FT_Err_Invalid_Version:		        LOG_ERROR("FreeType: Invalid FreeType version.");                   break;
	case FT_Err_Lower_Module_Version:	        LOG_ERROR("FreeType: Module version is too low.");                  break;
	case FT_Err_Invalid_Argument:		        LOG_ERROR("FreeType: Invalid argument.");                           break;
	case FT_Err_Unimplemented_Feature:	        LOG_ERROR("FreeType: Unimplemented feature.");                      break;
	case FT_Err_Invalid_Table:			        LOG_ERROR("FreeType: Invalid table.");                              break;
	case FT_Err_Invalid_Offset:			        LOG_ERROR("FreeType: Invalid offset.");                             break;
	case FT_Err_Array_Too_Large:		        LOG_ERROR("FreeType: Array allocation size too large.");            break;
	case FT_Err_Missing_Module:			        LOG_ERROR("FreeType: Missing module.");                             break;
	case FT_Err_Missing_Property:		        LOG_ERROR("FreeType: Missing property.");                           break;

		// Glyph/character errors
	case FT_Err_Invalid_Glyph_Index:	        LOG_ERROR("FreeType: Invalid glyph index.");                        break;
	case FT_Err_Invalid_Character_Code:	        LOG_ERROR("FreeType: Invalid character code.");                     break;
	case FT_Err_Invalid_Glyph_Format:	        LOG_ERROR("FreeType: Unsupported glyph format.");                   break;
	case FT_Err_Cannot_Render_Glyph:	        LOG_ERROR("FreeType: Cannot render this glyph format.");            break;
	case FT_Err_Invalid_Outline:		        LOG_ERROR("FreeType: Invalid outline.");                            break;
	case FT_Err_Invalid_Composite:		        LOG_ERROR("FreeType: Invalid composite glyph.");                    break;
	case FT_Err_Too_Many_Hints:			        LOG_ERROR("FreeType: Too many hints.");                             break;
	case FT_Err_Invalid_Pixel_Size:		        LOG_ERROR("FreeType: Invalid pixel size.");                         break;

		// Handle errors
	case FT_Err_Invalid_Handle:			        LOG_ERROR("FreeType: Invalid object handle.");                      break;
	case FT_Err_Invalid_Library_Handle:	        LOG_ERROR("FreeType: Invalid library handle.");                     break;
	case FT_Err_Invalid_Driver_Handle:	        LOG_ERROR("FreeType: Invalid module handle.");                      break;
	case FT_Err_Invalid_Face_Handle:	        LOG_ERROR("FreeType: Invalid face handle.");                        break;
	case FT_Err_Invalid_Size_Handle:	        LOG_ERROR("FreeType: Invalid size handle.");                        break;
	case FT_Err_Invalid_Slot_Handle:	        LOG_ERROR("FreeType: Invalid glyph slot handle.");                  break;
	case FT_Err_Invalid_CharMap_Handle:	        LOG_ERROR("FreeType: Invalid charmap handle.");                     break;
	case FT_Err_Invalid_Cache_Handle:	        LOG_ERROR("FreeType: Invalid cache manager handle.");               break;
	case FT_Err_Invalid_Stream_Handle:	        LOG_ERROR("FreeType: Invalid stream handle.");                      break;

		// Driver errors
	case FT_Err_Too_Many_Drivers:		        LOG_ERROR("FreeType: Too many modules.");                           break;
	case FT_Err_Too_Many_Extensions:	        LOG_ERROR("FreeType: Too many extensions.");                        break;

		// Memory errors
	case FT_Err_Out_Of_Memory:		            LOG_ERROR("FreeType: Out of memory.");                              break;
	case FT_Err_Unlisted_Object:	            LOG_ERROR("FreeType: Unlisted object.");                            break;

		// Stream errors
	case FT_Err_Cannot_Open_Stream:			    LOG_ERROR("FreeType: Cannot open stream.");                         break;
	case FT_Err_Invalid_Stream_Seek:		    LOG_ERROR("FreeType: Invalid stream seek.");                        break;
	case FT_Err_Invalid_Stream_Skip:		    LOG_ERROR("FreeType: Invalid stream skip.");                        break;
	case FT_Err_Invalid_Stream_Read:		    LOG_ERROR("FreeType: Invalid stream read.");                        break;
	case FT_Err_Invalid_Stream_Operation:	    LOG_ERROR("FreeType: Invalid stream operation.");                   break;
	case FT_Err_Invalid_Frame_Operation:	    LOG_ERROR("FreeType: Invalid frame operation.");                    break;
	case FT_Err_Nested_Frame_Access:		    LOG_ERROR("FreeType: Nested frame access.");                        break;
	case FT_Err_Invalid_Frame_Read:			    LOG_ERROR("FreeType: Invalid frame read.");                         break;

		// Raster errors
	case FT_Err_Raster_Uninitialized:	        LOG_ERROR("FreeType: Raster uninitialized.");                       break;
	case FT_Err_Raster_Corrupted:		        LOG_ERROR("FreeType: Raster corrupted.");                           break;
	case FT_Err_Raster_Overflow:		        LOG_ERROR("FreeType: Raster overflow.");                            break;
	case FT_Err_Raster_Negative_Height:	        LOG_ERROR("FreeType: Negative height while rastering.");            break;

		// Cache errors
	case FT_Err_Too_Many_Caches:	            LOG_ERROR("FreeType: Too many registered caches.");                 break;

		// TrueType and SFNT errors 
	case FT_Err_Invalid_Opcode:				    LOG_ERROR("FreeType: Invalid opcode.");                             break;
	case FT_Err_Too_Few_Arguments:			    LOG_ERROR("FreeType: Too few arguments.");                          break;
	case FT_Err_Stack_Overflow:				    LOG_ERROR("FreeType: Stack overflow.");                             break;
	case FT_Err_Code_Overflow:				    LOG_ERROR("FreeType: Code overflow.");                              break;
	case FT_Err_Bad_Argument:				    LOG_ERROR("FreeType: Bad argument.");                               break;
	case FT_Err_Divide_By_Zero:				    LOG_ERROR("FreeType: Division by zero.");                           break;
	case FT_Err_Invalid_Reference:			    LOG_ERROR("FreeType: Invalid reference.");                          break;
	case FT_Err_Debug_OpCode:				    LOG_ERROR("FreeType: Found debug opcode.");                         break;
	case FT_Err_ENDF_In_Exec_Stream:		    LOG_ERROR("FreeType: Found ENDF opcode in execution stream.");      break;
	case FT_Err_Nested_DEFS:				    LOG_ERROR("FreeType: Nested DEFS.");                                break;
	case FT_Err_Invalid_CodeRange:			    LOG_ERROR("FreeType: Invalid code range.");                         break;
	case FT_Err_Execution_Too_Long:			    LOG_ERROR("FreeType: Execution context too long.");                 break;
	case FT_Err_Too_Many_Function_Defs:		    LOG_ERROR("FreeType: Too many function definitions.");              break;
	case FT_Err_Too_Many_Instruction_Defs:	    LOG_ERROR("FreeType: Too many instruction definitions.");           break;
	case FT_Err_Table_Missing:				    LOG_ERROR("FreeType: SFNT font table missing.");                    break;
	case FT_Err_Horiz_Header_Missing:		    LOG_ERROR("FreeType: Horizontal header (hhea) table missing.");     break;
	case FT_Err_Locations_Missing:			    LOG_ERROR("FreeType: Locations (loca) table missing.");             break;
	case FT_Err_Name_Table_Missing:			    LOG_ERROR("FreeType: Name table missing.");                         break;
	case FT_Err_CMap_Table_Missing:			    LOG_ERROR("FreeType: Character map (cmap) table missing.");         break;
	case FT_Err_Hmtx_Table_Missing:			    LOG_ERROR("FreeType: Horizontal metrics (hmtx) table missing.");    break;
	case FT_Err_Post_Table_Missing:			    LOG_ERROR("FreeType: PostScript (post) table missing.");            break;
	case FT_Err_Invalid_Horiz_Metrics:		    LOG_ERROR("FreeType: Invalid horizontal metrics.");                 break;
	case FT_Err_Invalid_CharMap_Format:		    LOG_ERROR("FreeType: Invalid character map (cma) format.");         break;
	case FT_Err_Invalid_PPem:				    LOG_ERROR("FreeType: Invalid ppem value.");                         break;
	case FT_Err_Invalid_Vert_Metrics:		    LOG_ERROR("FreeType: Invalid vertical metrics.");                   break;
	case FT_Err_Could_Not_Find_Context:		    LOG_ERROR("FreeType: Could not find context.");                     break;
	case FT_Err_Invalid_Post_Table_Format:	    LOG_ERROR("FreeType: Invalid PostScript (post) table format.");     break;
	case FT_Err_Invalid_Post_Table:			    LOG_ERROR("FreeType: Invalid PostScript (post) table.");            break;
	case FT_Err_DEF_In_Glyf_Bytecode:		    LOG_ERROR("FreeType: Found FDEF or IDEF opcode in glyf bytecode."); break;

		// CFF, CID, and Type 1 errors 
	case FT_Err_Syntax_Error:			        LOG_ERROR("FreeType: Opcode syntax error.");                        break;
	case FT_Err_Stack_Underflow:		        LOG_ERROR("FreeType: Argument stack underflow.");                   break;
	case FT_Err_Ignore:					        LOG_ERROR("FreeType: Ignore.");                                     break;
	case FT_Err_No_Unicode_Glyph_Name:	        LOG_ERROR("FreeType: No Unicode glyph name found.");                break;
	case FT_Err_Glyph_Too_Big:			        LOG_ERROR("FreeType: Glyph too big for hinting.");                  break;

		// BDF errors
	case FT_Err_Missing_Startfont_Field:		LOG_ERROR("FreeType: 'STARTFONT' field missing.");                  break;
	case FT_Err_Missing_Font_Field:				LOG_ERROR("FreeType: 'FONT' field missing.");                       break;
	case FT_Err_Missing_Size_Field:				LOG_ERROR("FreeType: 'SIZE' field missing.");                       break;
	case FT_Err_Missing_Fontboundingbox_Field:	LOG_ERROR("FreeType: 'FONTBOUNDINGBOX' field missing.");            break;
	case FT_Err_Missing_Chars_Field:			LOG_ERROR("FreeType: 'CHARS' field missing.");                      break;
	case FT_Err_Missing_Startchar_Field:		LOG_ERROR("FreeType: 'STARTCHAR' field missing.");                  break;
	case FT_Err_Missing_Encoding_Field:			LOG_ERROR("FreeType: 'ENCODING' field missing.");                   break;
	case FT_Err_Missing_Bbx_Field:				LOG_ERROR("FreeType: 'BBX' field missing.");                        break;
	case FT_Err_Bbx_Too_Big:					LOG_ERROR("FreeType: 'BBX' too big.");                              break;
	case FT_Err_Corrupted_Font_Header:			LOG_ERROR("FreeType: Font header corrupted or missing fields.");    break;
	case FT_Err_Corrupted_Font_Glyphs:			LOG_ERROR("FreeType: Font glyphs corrupted or missing fields.");    break;

		// None
	default:                                    LOG_ERROR("FreeType: Unknown error code.");                         break;
	}

	return true;
}
