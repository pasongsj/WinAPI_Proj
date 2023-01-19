#pragma once

// 설명 :
class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	virtual ~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	inline bool IsUpdate()
	{
		//         조건          ?              true 일때                                      :         false 일때
		return nullptr != Parent ? ((ObjectUpdate && false == IsDeath()) && Parent->IsUpdate()) : (ObjectUpdate && false == ObjectDeath);

		// return nullptr != Parent ? 1000 : 200;
	}

	inline bool IsDeath()
	{
		return nullptr != Parent ? (true == ObjectDeath || Parent->IsDeath()) : (true == ObjectDeath);
	}

	inline void Death()
	{
		ObjectDeath = true;
	}

	inline void On()
	{
		ObjectUpdate = true;
	}
	inline void Off()
	{
		ObjectUpdate = false;
	}

	inline void OnOffSwtich()
	{
		ObjectUpdate = !ObjectUpdate;
	}


	inline void SetOwner(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	template<typename ConvertType>
	ConvertType* GetOwner()
	{
		return dynamic_cast<ConvertType*>(Parent);
	}

	GameEngineObject* GetOwner()
	{
		return Parent;
	}

protected:

private:
	GameEngineObject* Parent = nullptr;

	bool ObjectDeath = false;
	bool ObjectUpdate = true;

};

