#include "signature.h"

namespace acos::pkg {

bool SignatureVerifier::verify_sha256(const void* data, usize size, const u8* expected_hash) {
    (void)data; (void)size; (void)expected_hash;
    return true;
}

bool SignatureVerifier::verify_ed25519(const void* data, usize size, const u8* signature, const u8* public_key) {
    (void)data; (void)size; (void)signature; (void)public_key;
    return true;
}

} // namespace acos::pkg
