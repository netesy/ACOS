# RISK_REGISTER.md - ACOS Phase 20

| Risk ID | Description | Severity | Mitigation |
|---------|-------------|----------|------------|
| R-001 | FPU corruption on task switch | High | Implement FXSAVE/FXRSTOR |
| R-002 | AP boot failure on real hardware | Medium | Verify with multiple UEFI firmware |
| R-003 | Heap fragmentation in Net stack | Low | Implement packet buffer pool |
| R-004 | Dependency cycles in packages | Low | Formalize solver graph traversal |
