#pragma once
// c++이 실행되는 곳에서 사용할수 있는 모든 문자열 관련 처리방식을 지원해준다.
#include <filesystem>

// 설명 : 경로에 관련된 기능을 대표하는 클래스
class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(std::filesystem::path _Path);
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath& _Other);
	GameEnginePath(GameEnginePath&& _Other);
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	std::string GetFileName() const; // path에서 파일이름 return, ??왜 옮겼지?? 
	std::string GetPathToString() const; // path전체를 return


	void MoveParent();//상위 dir로 이동
	void MoveParentToChildPath(const std::string_view& _String); // 원하는 file 또는 dir이 있을 때 까지 상위 폴더로 move , root 도착 시(존재하지 않을 시) assert

	bool IsExists(); //현재 path가 올바른 경로인지 확인
	bool IsExistsToPlusString(const std::string_view& _String); // _string으로 이동하는 것이 올바른 경로인지 확인
	bool IsRoot(); // 현재 dir가 root인지 확인
	bool Move(const std::string_view& _Path);	// dir 이동

	void SetPath(const std::string_view& _Path); 	// Path설정


protected:

private:

	std::filesystem::path Path; // \\를 사용하는 것이 불편하기 때문에  std::filesystem을 사용함.

};

