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
		return nullptr != Parent ? ((ObjectUpdate && false == IsDeath()) && Parent->IsUpdate()) : (ObjectUpdate && false == ObjectDeath);
	}

	inline bool IsDeath()
	{
		return nullptr != Parent ? (true == ObjectDeath || Parent->IsDeath()) : (true == ObjectDeath);
	}

	inline void Death() //죽이는 기능
	{
		ObjectDeath = true;
	}

	inline void On() // update on
	{
		ObjectUpdate = true;
	}
	inline void Off() // update off
	{
		ObjectUpdate = false;
	}

	inline void OnOffSwtich()
	{
		ObjectUpdate = !ObjectUpdate;
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	int GetOrder()
	{
		return Order;
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

	int Order;
	bool ObjectDeath = false;
	bool ObjectUpdate = true;

};

