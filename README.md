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

### Why use it ⭐

* **Immediately useful** – every new project needs logging.
* **Single header** – low barrier to try and to vendor.
* **Well scoped** – easy to open small PRs (add syslog backend, JSON log, etc.).
* **Cross platform** – embedded & desktop devs alike benefit.

---

Feel free to copy‑paste `tinylog.h` above into its own repo.
