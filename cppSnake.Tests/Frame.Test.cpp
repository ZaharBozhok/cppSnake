#include "pch.h"
#include "Frame.h"

Frame CreateFrame()
{
    return Frame(4, 4);
}

TEST(FrameTest, FrameInitialized_SizePassed_RightWidth)
{
    Frame frame = CreateFrame();

    EXPECT_EQ(frame.Width(), 4);
}

TEST(FrameTest, FrameInitialized_SizePassed_RightHeight)
{
    Frame frame = CreateFrame();

    EXPECT_EQ(frame.Height(), 4);
}

// Set Point

TEST(FrameTest, SetCell_NormalValuePoint_ProperCellSet)
{
    Frame frame = CreateFrame();
    Point point = { 1,1 };
    frame.Set(point, L'A');

    EXPECT_EQ(L'A', frame.Buffer()[5]);
}

TEST(FrameTest, SetCell_NormalValue_ProperCellSet)
{
    Frame frame = CreateFrame();
    size_t point = 10;
    frame.Set(point, L'A');

    EXPECT_EQ(L'A', frame.Buffer()[point]);
}

TEST(FrameTest, SetCell_OutOfRangePointValue_ThrowsOutOfRange)
{
    Frame frame = CreateFrame();
    Point point = { 10,10 };

    EXPECT_THROW(
        frame.Set(point, wchar_t()),
        std::out_of_range
    );
}

TEST(FrameTest, SetCell_OutOfRangeLengthValue_ThrowsOutOfRange)
{
    Frame frame = CreateFrame();
    size_t point = 100;

    EXPECT_THROW(
        frame.Set(point, wchar_t()),
        std::out_of_range
    );
}

//Get Point

TEST(FrameTest, GetCell_NormalValue_ReturnsProperValue)
{
    Frame frame = CreateFrame();
    frame.Buffer()[5] = L'A';

    EXPECT_EQ(L'A', frame.Get(5));
}

TEST(FrameTest, GetCell_NormalValuePoint_ReturnsProperValue)
{
    Frame frame = CreateFrame();
    Point point{ 0,1 };
    frame.Buffer()[4] = L'A';

    EXPECT_EQ(L'A', frame.Get(point));
}

TEST(FrameTest, GetCell_OutOfRangePosition_ThrowsOutOfRange)
{
    Frame frame = CreateFrame();
    size_t point = 100;

    EXPECT_THROW(
        frame.Get(point),
        std::out_of_range
    );
}

TEST(FrameTest, GetCell_OutOfRangePoint_ThrowsOutOfRange)
{
    Frame frame = CreateFrame();
    Point point{ 10, 10 };

    EXPECT_THROW(
        frame.Get(point),
        std::out_of_range
    );
}

// Raw buffer

TEST(FrameTest, GetBuffer_NotNull)
{
    Frame frame = CreateFrame();

    EXPECT_NE(frame.Buffer(), nullptr);
}