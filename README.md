# tinylog

> 🪶 A 1‑file logging utility for C projects (embedded, POSIX, Windows).

```c
#define TINYLOG_IMPLEMENTATION
#include "tinylog.h"

int main(void) {
    LOG_INFO("system up");
    LOG_DEBUG("val=%d", 42);
}
```

### Why this attracts contributors ⭐

* **Immediately useful** – every new project needs logging.
* **Single header** – low barrier to try and to vendor.
* **Well scoped** – easy to open small PRs (add syslog backend, JSON log, etc.).
* **Cross platform** – embedded & desktop devs alike benefit.

---

## Next steps for your collection

| Task | Tip |
|------|-----|
| **Pick a license** | MIT or Apache‑2.0 keeps it friction‑free. |
| **Add examples** | Show desktop + STM32/NXP bare‑metal demo. |
| **Unit tests** | e.g. `ctest` with clang/gcc on CI (GitHub Actions). |
| **Tag v1.0.0** | Semantic version so users can pin. |

Feel free to copy‑paste `tinylog.h` above into its own repo. When you’re ready for the next module (ring buffer or FSM helper), let me know and I can craft those too!
