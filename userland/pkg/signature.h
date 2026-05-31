#pragma once
#include <acos/types.h>

namespace acos::pkg {

class SignatureVerifier {
public:
    static bool verify_sha256(const void* data, usize size, const u8* expected_hash);
    static bool verify_ed25519(const void* data, usize size, const u8* signature, const u8* public_key);
};

} // namespace acos::pkg
