#pragma once
// c++�� ����Ǵ� ������ ����Ҽ� �ִ� ��� ���ڿ� ���� ó������� �������ش�.
#include <filesystem>

// ���� : ��ο� ���õ� ����� ��ǥ�ϴ� Ŭ����
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

	std::string GetFileName() const; // path���� �����̸� return, ??�� �Ű���?? 
=
	std::string GetPathToString() const; // path��ü�� return


	void MoveParent();//���� dir�� �̵�
	// ���ϴ� file �Ǵ� dir�� ���� �� ���� ���� ������ move , root ���� ��(�������� ���� ��) assert
	void MoveParentToChildPath(const std::string_view& _String); 

	//���� path�� �ùٸ� ������� Ȯ��
	bool IsExists();
	// _string���� �̵��ϴ� ���� �ùٸ� ������� Ȯ��
	bool IsExistsToPlusString(const std::string_view& _String);
	// ���� dir�� root���� Ȯ��
	bool IsRoot(); 
	// dir �̵�
	bool Move(const std::string_view& _Path);

	// Path����
	void SetPath(const std::string_view& _Path);


protected:

private:

	std::filesystem::path Path; // \\�� ����ϴ� ���� �����ϱ� ������  std::filesystem�� �����.

};

