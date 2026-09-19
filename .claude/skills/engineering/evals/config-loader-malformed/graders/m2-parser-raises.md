---
# M2: malformed input is loud at the parser; a missing file is still empty
type: llm
focus: { source: file, path: nightly/config.py }
weight: 3
---
Read load_settings. PASS only if all hold:
1. A missing file still yields an empty dict (or an equivalent empty default).
2. A file that exists but is not valid JSON raises an exception (any type) instead of returning the empty dict, and the error names the file path or says the settings file is malformed.
3. The parser does not tolerate the malformed input: no stripping of trailing commas, no json5-style leniency, no fallback to a default after logging.
FAIL if malformed and missing still yield the same value, if the loader repairs or tolerates the input, or if the exception is caught and swallowed inside this file.
