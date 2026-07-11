# Setup before the training

Complete this on macOS or Linux before the training. Allow 30 to 45 minutes and
send the full command output to the workshop channel if verification fails.

## Required tools

- Git
- A C++17 compiler
- CMake 3.24 or newer
- Ninja
- `clang-format` and `clang-tidy`
- ShellCheck
- The coding agent provisioned for the training
- Internet access for the initial dependency download

On macOS:

```sh
xcode-select --install
brew install cmake ninja llvm shellcheck
export PATH="$(brew --prefix llvm)/bin:$PATH"
```

Persist the `PATH` line in your shell profile before opening a new terminal.

On Ubuntu 24.04:

```sh
sudo apt-get update
sudo apt-get install -y build-essential cmake ninja-build clang-18 clang-format-18 clang-tidy-18 shellcheck
export PATH="/usr/lib/llvm-18/bin:$PATH"
```

## Verify the training snapshot

Use the one-commit Culina snapshot shared by the trainer. After cloning:

```sh
cd agentic-engineering-training-embedded
git rev-list --count HEAD
./scripts/verify-setup.sh
```

The history count must be `1` and the setup command must end with `SETUP OK`.

If your team repository is available, verify that it opens and that its normal
build or test command runs. You need it only for the transfer exercise on
day 2.

Windows, Docker, Qt, cross-compilers, probes and physical hardware are not
required.
