#include <Pineapple/Engine/Container/Bitfield.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

enum class SimpleFlags
{
	One,
	Two,
	Three,
	is_enum_bitfield
};

TEST(Bitfield, SetAndGet)
{
	pa::Bitfield<SimpleFlags> SUT;

	ASSERT_FALSE(SUT.getBool(SimpleFlags::One));
	ASSERT_FALSE(SUT.getBool(SimpleFlags::Two));
	ASSERT_FALSE(SUT.getBool(SimpleFlags::Three));

	SUT.set(SimpleFlags::One);

	ASSERT_TRUE(SUT.getBool(SimpleFlags::One));
	ASSERT_FALSE(SUT.getBool(SimpleFlags::Two));
	ASSERT_FALSE(SUT.getBool(SimpleFlags::Three));

	SUT.set(SimpleFlags::Two);

	ASSERT_TRUE(SUT.getBool(SimpleFlags::One));
	ASSERT_TRUE(SUT.getBool(SimpleFlags::Two));
	ASSERT_FALSE(SUT.getBool(SimpleFlags::Three));

	SUT.set(SimpleFlags::Three);

	ASSERT_TRUE(SUT.getBool(SimpleFlags::One));
	ASSERT_TRUE(SUT.getBool(SimpleFlags::Two));
	ASSERT_TRUE(SUT.getBool(SimpleFlags::Three));
}

TEST(Bitfield, ClearAndGet)
{
	pa::Bitfield<SimpleFlags> SUT;

	SUT.set(SimpleFlags::One);
	SUT.set(SimpleFlags::Two);
	SUT.set(SimpleFlags::Three);

	ASSERT_TRUE(SUT.getBool(SimpleFlags::One));
	ASSERT_TRUE(SUT.getBool(SimpleFlags::Two));
	ASSERT_TRUE(SUT.getBool(SimpleFlags::Three));

	SUT.clear(SimpleFlags::One);

	ASSERT_FALSE(SUT.getBool(SimpleFlags::One));
	ASSERT_TRUE(SUT.getBool(SimpleFlags::Two));
	ASSERT_TRUE(SUT.getBool(SimpleFlags::Three));

	SUT.clear(SimpleFlags::Two);

	ASSERT_FALSE(SUT.getBool(SimpleFlags::One));
	ASSERT_FALSE(SUT.getBool(SimpleFlags::Two));
	ASSERT_TRUE(SUT.getBool(SimpleFlags::Three));

	SUT.clear(SimpleFlags::Three);

	ASSERT_FALSE(SUT.getBool(SimpleFlags::One));
	ASSERT_FALSE(SUT.getBool(SimpleFlags::Two));
	ASSERT_FALSE(SUT.getBool(SimpleFlags::Three));
}

TEST(Bitfield, GetBitwise)
{
	pa::Bitfield<SimpleFlags> SUT;

	SUT.set(SimpleFlags::One);
	SUT.set(SimpleFlags::Three);

	ASSERT_TRUE((SUT.get(SimpleFlags::One) | SUT.get(SimpleFlags::Three)) == 0b101);
}

enum class Uint8Flags1
{
	is_enum_bitfield
};

enum class Uint8Flags2
{
	Flag = 7,
	is_enum_bitfield
};

enum class Uint16Flags1
{
	Flag = 8,
	is_enum_bitfield
};

enum class Uint16Flags2
{
	Flag = 15,
	is_enum_bitfield
};

enum class Uint32Flags1
{
	Flag = 16,
	is_enum_bitfield
};

enum class Uint32Flags2
{
	Flag = 31,
	is_enum_bitfield
};

enum class Uint64Flags1
{
	Flag = 32,
	is_enum_bitfield
};

enum class Uint64Flags2
{
	Flag = 63,
	is_enum_bitfield
};

TEST(Bitfield, StorageSize)
{
	bool condition = std::is_same<pa::Bitfield<Uint8Flags1>::Storage, std::uint8_t>::value;
	ASSERT_TRUE(condition);
	condition = std::is_same<pa::Bitfield<Uint8Flags2>::Storage, std::uint8_t>::value;
	ASSERT_TRUE(condition);
	condition = std::is_same<pa::Bitfield<Uint16Flags1>::Storage, std::uint16_t>::value;
	ASSERT_TRUE(condition);
	condition = std::is_same<pa::Bitfield<Uint16Flags2>::Storage, std::uint16_t>::value;
	ASSERT_TRUE(condition);
	condition = std::is_same<pa::Bitfield<Uint32Flags1>::Storage, std::uint32_t>::value;
	ASSERT_TRUE(condition);
	condition = std::is_same<pa::Bitfield<Uint32Flags2>::Storage, std::uint32_t>::value;
	ASSERT_TRUE(condition);
	condition = std::is_same<pa::Bitfield<Uint64Flags1>::Storage, std::uint64_t>::value;
	ASSERT_TRUE(condition);
	condition = std::is_same<pa::Bitfield<Uint64Flags2>::Storage, std::uint64_t>::value;
	ASSERT_TRUE(condition);
}