#include <gtest/gtest.h>

extern "C" {
    #include "decoder.h"
}

uint8_t tag1Cbor[] = { 0xC0, 0x63, 0x61, 0x62, 0x63 };  // 0("abc")
uint8_t tag1ContentCbor[] = { 0x63, 0x61, 0x62, 0x63 }; // "abc"

TEST(tagTest, tagTest) {
    DataItem *tag1Item = microCBORDecode(tag1Cbor);
    DataItem *tag1ContentItem = tag1Item->content;

    EXPECT_EQ(tag1Item->header, 0xC0);
    EXPECT_EQ(tag1ContentItem->header, 0x63);
    EXPECT_EQ(tag1ContentItem->payload[0], 0x61);
    EXPECT_EQ(tag1ContentItem->payload[1], 0x62);
    EXPECT_EQ(tag1ContentItem->payload[2], 0x63);
}