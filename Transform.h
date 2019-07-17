#pragma once

template<typename T>
struct Property
{
	std::function<T()> Getter;
	std::function<void(const T& value)> Setter;
	Property(
		const std::function<T()>& Getter,
		const std::function<void(const T&)>& Setter)
		: Getter(Getter)
		, Setter(Setter)
	{}
	void operator=(const T& value) { Setter(value); }
	operator T() const { return Getter(); }
	void operator+=(const T& value) { Setter(Getter() + value); }
	void operator-=(const T& value) { Setter(Getter() - value); }
	void operator*=(const T& value) { Setter(Getter() * value); }
	void operator/=(const T& value) { Setter(Getter() / value); }
	void operator%=(const T& value) { Setter(Getter() % value); }
	T operator*() const { return Getter(); }
	T operator->() const { return Getter(); }
};

// Transformクラス
class Transform
{
public:
	// コンストラクタ
	Transform::Transform()
		: parent(nullptr)
		, localPosition(DirectX::SimpleMath::Vector3::Zero)
		, localRotation(DirectX::SimpleMath::Quaternion::Identity)
		, localScale(DirectX::SimpleMath::Vector3::One)
	{
	}

public:
	// ローカル位置
	DirectX::SimpleMath::Vector3 localPosition;
	// ローカル回転
	DirectX::SimpleMath::Quaternion localRotation;
	// ローカルスケール
	DirectX::SimpleMath::Vector3 localScale;

	Property<DirectX::SimpleMath::Vector3> position
	{
		[&]()
		{
			if (parent)
				return DirectX::SimpleMath::Vector3::Transform(localPosition, parent->GetMatrix().Invert());
			else
				return localPosition;
		},
		[&](const DirectX::SimpleMath::Vector3& value)
		{
			if (parent)
				localPosition = DirectX::SimpleMath::Vector3::Transform(value, parent->GetMatrix());
			else
				localPosition = value;
		}
	};

	Property<DirectX::SimpleMath::Quaternion> rotation
	{
		[&]()
		{
			if (parent)
				return localRotation * DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(parent->GetMatrix().Invert());
			else
				return localRotation;
		},
		[&](const DirectX::SimpleMath::Quaternion& value)
		{
			if (parent)
				localRotation = value * DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(parent->GetMatrix());
			else
				localRotation = value;
		}
	};

	Property<DirectX::SimpleMath::Vector3> lossyScale
	{
		[&]()
		{
			if (parent)
				return DirectX::SimpleMath::Vector3::Transform(localScale, parent->GetMatrix().Invert());
			else
				return localScale;
		},
		[&](const DirectX::SimpleMath::Vector3& value)
		{
			if (parent)
				localScale = DirectX::SimpleMath::Vector3::Transform(value, parent->GetMatrix());
			else
				localScale = value;
		}
	};

	const Transform* parent;
	void SetParent(const Transform* value)
	{
		DirectX::SimpleMath::Vector3 worldPosition = position;
		DirectX::SimpleMath::Quaternion worldRotation = rotation;
		DirectX::SimpleMath::Vector3 worldScale = lossyScale;
		parent = value;
		position = worldPosition;
		rotation = worldRotation;
		lossyScale = worldScale;
	}

	// 行列取得
	DirectX::SimpleMath::Matrix GetMatrix() const
	{
		return
			DirectX::SimpleMath::Matrix::CreateScale(localScale) *
			DirectX::SimpleMath::Matrix::CreateFromQuaternion(localRotation) *
			DirectX::SimpleMath::Matrix::CreateTranslation(localPosition) *
			(parent != nullptr ? parent->GetMatrix() : DirectX::SimpleMath::Matrix::Identity);
	}
};