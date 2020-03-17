#pragma once

enum class HintingType : uint
{
	None,
	Light,
	Normal
};

struct Glyph final
{
	int left;
	int right;
	int top;
	int bottom;
	int width;
	int height;
	float uv_left;
	float uv_right;
	float uv_top;
	float uv_bottom;
	int descent;
	int space_offset;
	int horizontal_offset;
};

struct Glyphs
{
	std::map<int, Glyph> glyphs;
	uint maxWidth;
	uint maxHeight;
	uint fontSize;
	bool isForceAutoHint;
	HintingType hintingType;
	std::string path;
	std::string name;
};

//������ �� glyphs ���� ��������
//Resource Manager �� texture ���� �ĳ־� �δ� ����
//mesh �鵵 ���� ����� ���� ����
//�׸��� font ������ mesh�� �̾Ƽ� ���°���
//material �� ���� ���� �ʿ� ����
//�׷��ϱ� ��� resource �� ������

// Glyph metrics:
// --------------
//
//                       xmin                     xmax
//                        |                         |
//                        |<-------- width -------->|
//                        |                         |
//              |         +-------------------------+----------------- ymax
//              |         |    ggggggggg   ggggg    |     ^        ^
//              |         |   g:::::::::ggg::::g    |     |        |
//              |         |  g:::::::::::::::::g    |     |        |
//              |         | g::::::ggggg::::::gg    |     |        |
//              |         | g:::::g     g:::::g     |     |        |
//    offsetX  -|-------->| g:::::g     g:::::g     |  offsetY     |
//              |         | g:::::g     g:::::g     |     |        |
//              |         | g::::::g    g:::::g     |     |        |
//              |         | g:::::::ggggg:::::g     |     |        |
//              |         |  g::::::::::::::::g     |     |      height
//              |         |   gg::::::::::::::g     |     |        |
//  baseline ---*---------|---- gggggggg::::::g-----*--------      |
//            / |         |             g:::::g     |              |
//     origin   |         | gggggg      g:::::g     |              |
//              |         | g:::::gg   gg:::::g     |              |
//              |         |  g::::::ggg:::::::g     |              |
//              |         |   gg:::::::::::::g      |              |
//              |         |     ggg::::::ggg        |              |
//              |         |         gggggg          |              v
//              |         +-------------------------+----------------- ymin
//              |                                   |
//              |------------- advanceX


class FontImporter final
{
public:
	FontImporter(class Context* context);
	~FontImporter();

	const bool LoadFromFile(Glyphs& glyphs);
	const bool SetText(const std::string& glyphsName, const std::wstring& text, class Renderable* renderable, class Transform* transform);

private:
	void ComputeAtlasTextureDimension(struct FT_FaceRec_* face, uint& altasWidth, uint& altas, uint& rowHeight);
	const int GetCharacterMaxHeight(struct FT_FaceRec_* face);
	const bool ErrorHandler(const int& errorCode);

private:
	std::map<std::string, Glyphs> glyphsMap;     // importer
	Context* context;
	ResourceManager* resourceManager;
};