# Watchline

**Watchline** is a Full feature Internet Control Center GNOME app. It is currently under active development.

---

## Goal

To provide a reliable, privacy-respecting Internet control center for:

- Internet speed testing
- Bandwidth usage tracking
- Connection stability analysis
- Restriction and throttling detection
- DNS settings, etc

---

## Status

**Coming Soon**

The current version supports basic speed testing via `speedtest-cli`. Additional features are planned and under construction.

---

## Contributing

We welcome contributions that improve performance, usability, and clarity.

### Build Instructions

```bash
git clone https://github.com/soroushgh1/watchline.git
cd watchline
mkdir -p build
cd build
cmake ..
make 
./App
```

### Guidelines

- Use clear, modular code—prefer explicit control over abstraction
- Follow GTKmm 4 
- Submit pull requests with descriptive commits and rationale
- Respect the minimal design language and avoid unnecessary dependencies

---

## License

MIT
