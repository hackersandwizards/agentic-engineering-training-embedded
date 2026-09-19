#!/usr/bin/env bash
# Deploy tooling for a CLI called acmectl. The flag --legacy-auth is used in two visible files
# (scripts/deploy.sh, docs/deploy.md) and in three hidden paths a default rg or fd sweep skips:
# .github/workflows/ci.yml, .devcontainer/post-create.sh and the dotfile .acmectl.env. The flag
# string starts with a dash, so an unguarded grep or rg reads it as an option. No environment:
# git and coreutils.
set -euo pipefail
git -c init.defaultBranch=main init -q
git config user.email mara@example.com
git config user.name "Mara Vogt"
git config commit.gpgsign false
mkdir -p scripts docs .github/workflows .devcontainer

cat > README.md <<'MD'
# acmectl deploy tooling

Wraps the `acmectl` CLI for staging and production deploys. CI runs `.github/workflows/ci.yml`
on ubuntu-latest; developers work in the devcontainer or on their own machines with the
settings from `.acmectl.env`.
MD

cat > scripts/deploy.sh <<'SH'
#!/bin/sh
set -eu
ENV="${1:-staging}"
acmectl login --legacy-auth
acmectl deploy --env "$ENV" --wait
SH

cat > scripts/rollback.sh <<'SH'
#!/bin/sh
set -eu
ENV="${1:-staging}"
acmectl rollback --env "$ENV" --to previous
SH

cat > scripts/lint.sh <<'SH'
#!/bin/sh
set -eu
for f in scripts/*.sh; do
  sh -n "$f"
done
SH
chmod +x scripts/deploy.sh scripts/rollback.sh scripts/lint.sh

cat > Makefile <<'MK'
check:
	sh scripts/lint.sh

deploy:
	sh scripts/deploy.sh staging
MK

cat > .github/workflows/ci.yml <<'YML'
name: ci
on: [push]
jobs:
  verify:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - run: make check
      - run: acmectl verify --legacy-auth --env staging
YML

cat > .devcontainer/post-create.sh <<'SH'
#!/bin/sh
set -eu
acmectl login --legacy-auth --profile dev
SH
chmod +x .devcontainer/post-create.sh

cat > .acmectl.env <<'ENV'
ACMECTL_PROFILE=dev
ACMECTL_LOGIN_ARGS="--legacy-auth"
ENV

cat > docs/deploy.md <<'MD'
# Deploying

Run `acmectl login --legacy-auth` once per session, then `make deploy`. Rollback with
`sh scripts/rollback.sh <env>`.
MD

printf 'dist/\n' > .gitignore
git add .gitignore README.md Makefile scripts/deploy.sh scripts/rollback.sh scripts/lint.sh \
  .github/workflows/ci.yml .devcontainer/post-create.sh .acmectl.env docs/deploy.md
git commit -q -m "deploy tooling for acmectl"
