# MaterialSystemFix

[![CI](https://github.com/ThisAMJ/materialsystemfix/actions/workflows/CI.yml/badge.svg)](https://github.com/ThisAMJ/materialsystemfix/actions/workflows/CI.yml)

This is a plugin for [Portal 2](https://store.steampowered.com/app/620) mods that fixes a bug in the game's
`materialsystem` library. The bug causes mods with any other game directory
(`-game` parameter) than `portal2` to allocate a measly 2MB of memory to the
material system, which is not enough for large maps or complex mods.

This plugin fixes the bug by patching the library to allocate the same amount
of memory as for the `portal2` game directory.

If you're interested, the relevant function is `CMatRenderContextBase::Init`.

## Installation

1. Download the latest release from the [releases page](https://github.com/ThisAMJ/materialsystemfix/releases).
2. Place `materialsystemfix.dll` and `materialsystemfix.so` in your mod's game directory.
3. Add `plugin_load materialsystemfix` to `cfg/valve.rc` or `cfg/autoexec.cfg`.
    - It does not have to run on launch, but it is recommended.
    - You can also create `addons/materialsystemfix.vdf` with the content `"plugin"{"file" "materialsystemfix"}`

## Building

### Windows

You'll need:

- [Visual Studio Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/)
- Windows SDK 10.0.18362.0
- Platform toolset v142

```batch
msbuild -m -t:materialsystemfix -p:"Platform=x86" MSF.sln
```

### Linux

You'll need:

- `g++-10-multilib`

```bash
make -j$(nproc)
```
