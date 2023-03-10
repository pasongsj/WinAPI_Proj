#pragma once
#include <string_view>
#include <vector>
#include "GameEnginePath.h"


// 설명 : directory를 관리하는 class
class GameEngineFile;
class GameEngineDirectory
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	// 이 디렉토리에 이 파일이 있어?
	bool IsFile(const std::string_view& _FileName);

	bool MoveParent(); // 부모 dir로 이동

	void MoveParentToDirectory(const std::string_view& _String);

	bool Move(const std::string_view& _String);

	GameEnginePath GetPlusFileName(const std::string_view& _String);


	std::vector<GameEngineFile> GetAllFile(const std::string_view& _Ext = "");

	// void MoveParent();

protected:

private:
	// "D:\Project\AR45\WINAPI\APIApp\ContentsResources\Iamge\";
	GameEnginePath Path;
};

