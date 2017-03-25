#include <gtest/gtest.h>

#include "crypto.hpp"


TEST(Base64Encode, Basic) {
    EXPECT_EQ(electronpass::Crypto::base64_encode("Test"), "VGVzdA==");
    EXPECT_EQ(electronpass::Crypto::base64_encode("Hello, World!"), "SGVsbG8sIFdvcmxkIQ==");

    EXPECT_EQ(electronpass::Crypto::base64_encode(""), "");

    EXPECT_EQ(electronpass::Crypto::base64_encode("Sample text."), "U2FtcGxlIHRleHQu");
    EXPECT_EQ(electronpass::Crypto::base64_encode("Sample text"), "U2FtcGxlIHRleHQ=");
    EXPECT_EQ(electronpass::Crypto::base64_encode("Sample tex"), "U2FtcGxlIHRleA==");
    EXPECT_EQ(electronpass::Crypto::base64_encode("Sample te"), "U2FtcGxlIHRl");
    EXPECT_EQ(electronpass::Crypto::base64_encode("Sample t"), "U2FtcGxlIHQ=");

    EXPECT_EQ(electronpass::Crypto::base64_encode("ZHVja2R1Y2tnbw=="), "WkhWamEyUjFZMnRuYnc9PQ==");

    EXPECT_EQ(electronpass::Crypto::base64_encode(
        "magni eum voluptatibus vel et velit sapiente expedita natus vitae"),
        "bWFnbmkgZXVtIHZvbHVwdGF0aWJ1cyB2ZWwgZXQgdmVsaXQgc2FwaWVudGUgZXhwZWRpdGEgbmF0dXMgdml0YWU="
    );
    EXPECT_EQ(electronpass::Crypto::base64_encode(
        "Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque "
        "laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi "
        "architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas "
        "sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione "
        "voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit "
        "amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut "
        "labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis "
        "nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi "
        "consequatur? Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam "
        "nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?"
        ),
        "U2VkIHV0IHBlcnNwaWNpYXRpcyB1bmRlIG9tbmlzIGlzdGUgbmF0dXMgZXJyb3Igc2l0IHZvbHVwdGF0ZW0gYWNjdX"
        "NhbnRpdW0gZG9sb3JlbXF1ZSBsYXVkYW50aXVtLCB0b3RhbSByZW0gYXBlcmlhbSwgZWFxdWUgaXBzYSBxdWFlIGFi"
        "IGlsbG8gaW52ZW50b3JlIHZlcml0YXRpcyBldCBxdWFzaSBhcmNoaXRlY3RvIGJlYXRhZSB2aXRhZSBkaWN0YSBzdW"
        "50IGV4cGxpY2Fiby4gTmVtbyBlbmltIGlwc2FtIHZvbHVwdGF0ZW0gcXVpYSB2b2x1cHRhcyBzaXQgYXNwZXJuYXR1"
        "ciBhdXQgb2RpdCBhdXQgZnVnaXQsIHNlZCBxdWlhIGNvbnNlcXV1bnR1ciBtYWduaSBkb2xvcmVzIGVvcyBxdWkgcm"
        "F0aW9uZSB2b2x1cHRhdGVtIHNlcXVpIG5lc2NpdW50LiBOZXF1ZSBwb3JybyBxdWlzcXVhbSBlc3QsIHF1aSBkb2xv"
        "cmVtIGlwc3VtIHF1aWEgZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyLCBhZGlwaXNjaSB2ZWxpdCwgc2VkIHF1aW"
        "Egbm9uIG51bXF1YW0gZWl1cyBtb2RpIHRlbXBvcmEgaW5jaWR1bnQgdXQgbGFib3JlIGV0IGRvbG9yZSBtYWduYW0g"
        "YWxpcXVhbSBxdWFlcmF0IHZvbHVwdGF0ZW0uIFV0IGVuaW0gYWQgbWluaW1hIHZlbmlhbSwgcXVpcyBub3N0cnVtIG"
        "V4ZXJjaXRhdGlvbmVtIHVsbGFtIGNvcnBvcmlzIHN1c2NpcGl0IGxhYm9yaW9zYW0sIG5pc2kgdXQgYWxpcXVpZCBl"
        "eCBlYSBjb21tb2RpIGNvbnNlcXVhdHVyPyBRdWlzIGF1dGVtIHZlbCBldW0gaXVyZSByZXByZWhlbmRlcml0IHF1aS"
        "BpbiBlYSB2b2x1cHRhdGUgdmVsaXQgZXNzZSBxdWFtIG5paGlsIG1vbGVzdGlhZSBjb25zZXF1YXR1ciwgdmVsIGls"
        "bHVtIHF1aSBkb2xvcmVtIGV1bSBmdWdpYXQgcXVvIHZvbHVwdGFzIG51bGxhIHBhcmlhdHVyPw=="
    );
}

TEST(Base64Decode, Basic) {
    EXPECT_EQ(electronpass::Crypto::base64_decode("VGVzdA=="), "Test");
    EXPECT_EQ(electronpass::Crypto::base64_decode("SGVsbG8sIFdvcmxkIQ=="), "Hello, World!");

    EXPECT_EQ(electronpass::Crypto::base64_decode(""), "");

    EXPECT_EQ(electronpass::Crypto::base64_decode("U2FtcGxlIHRleHQu"), "Sample text.");
    EXPECT_EQ(electronpass::Crypto::base64_decode("U2FtcGxlIHRleHQ="), "Sample text");
    EXPECT_EQ(electronpass::Crypto::base64_decode("U2FtcGxlIHRleA=="), "Sample tex");
    EXPECT_EQ(electronpass::Crypto::base64_decode("U2FtcGxlIHRl"), "Sample te");
    EXPECT_EQ(electronpass::Crypto::base64_decode("U2FtcGxlIHQ="), "Sample t");

    EXPECT_EQ(electronpass::Crypto::base64_decode("WkhWamEyUjFZMnRuYnc9PQ=="), "ZHVja2R1Y2tnbw==");

    EXPECT_EQ(electronpass::Crypto::base64_decode(
        "bWFnbmkgZXVtIHZvbHVwdGF0aWJ1cyB2ZWwgZXQgdmVsaXQgc2FwaWVudGUgZXhwZWRpdGEgbmF0dXMgdml0YWU="),
        "magni eum voluptatibus vel et velit sapiente expedita natus vitae"
    );
    EXPECT_EQ(electronpass::Crypto::base64_decode(
        "U2VkIHV0IHBlcnNwaWNpYXRpcyB1bmRlIG9tbmlzIGlzdGUgbmF0dXMgZXJyb3Igc2l0IHZvbHVwdGF0ZW0gYWNjdX"
        "NhbnRpdW0gZG9sb3JlbXF1ZSBsYXVkYW50aXVtLCB0b3RhbSByZW0gYXBlcmlhbSwgZWFxdWUgaXBzYSBxdWFlIGFi"
        "IGlsbG8gaW52ZW50b3JlIHZlcml0YXRpcyBldCBxdWFzaSBhcmNoaXRlY3RvIGJlYXRhZSB2aXRhZSBkaWN0YSBzdW"
        "50IGV4cGxpY2Fiby4gTmVtbyBlbmltIGlwc2FtIHZvbHVwdGF0ZW0gcXVpYSB2b2x1cHRhcyBzaXQgYXNwZXJuYXR1"
        "ciBhdXQgb2RpdCBhdXQgZnVnaXQsIHNlZCBxdWlhIGNvbnNlcXV1bnR1ciBtYWduaSBkb2xvcmVzIGVvcyBxdWkgcm"
        "F0aW9uZSB2b2x1cHRhdGVtIHNlcXVpIG5lc2NpdW50LiBOZXF1ZSBwb3JybyBxdWlzcXVhbSBlc3QsIHF1aSBkb2xv"
        "cmVtIGlwc3VtIHF1aWEgZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyLCBhZGlwaXNjaSB2ZWxpdCwgc2VkIHF1aW"
        "Egbm9uIG51bXF1YW0gZWl1cyBtb2RpIHRlbXBvcmEgaW5jaWR1bnQgdXQgbGFib3JlIGV0IGRvbG9yZSBtYWduYW0g"
        "YWxpcXVhbSBxdWFlcmF0IHZvbHVwdGF0ZW0uIFV0IGVuaW0gYWQgbWluaW1hIHZlbmlhbSwgcXVpcyBub3N0cnVtIG"
        "V4ZXJjaXRhdGlvbmVtIHVsbGFtIGNvcnBvcmlzIHN1c2NpcGl0IGxhYm9yaW9zYW0sIG5pc2kgdXQgYWxpcXVpZCBl"
        "eCBlYSBjb21tb2RpIGNvbnNlcXVhdHVyPyBRdWlzIGF1dGVtIHZlbCBldW0gaXVyZSByZXByZWhlbmRlcml0IHF1aS"
        "BpbiBlYSB2b2x1cHRhdGUgdmVsaXQgZXNzZSBxdWFtIG5paGlsIG1vbGVzdGlhZSBjb25zZXF1YXR1ciwgdmVsIGls"
        "bHVtIHF1aSBkb2xvcmVtIGV1bSBmdWdpYXQgcXVvIHZvbHVwdGFzIG51bGxhIHBhcmlhdHVyPw=="
        ),
        "Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque "
        "laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi "
        "architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas "
        "sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione "
        "voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit "
        "amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut "
        "labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis "
        "nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi "
        "consequatur? Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam "
        "nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?"
    );

}
