# Slack Channel Mechanics

Slack format constraints layered on the base voice rules: MCP-tool markdown quirks, message length tiers, channel-specific greeting/closing carve-outs. Apply when sending or drafting any Slack message via the Slack MCP tool.

## Slack markdown via the MCP tool

The MCP Slack tool accepts **standard markdown**, not Slack's own mrkdwn syntax, and converts it.

| Format | Correct syntax | Wrong | Failure mode |
|--------|---------------|-------|--------------|
| Bold | `**text**` (double asterisks) | `*text*` | Single-asterisks render as italic |
| Italic | `*text*` (single asterisks) | | `_text_` also works |
| Bold + Italic | `_**text**_` or `**_text_**` | `*_text_*` | Wrap one inside the other |
| Strikethrough | `~~text~~` (double tilde) | | `~text~` also works |
| Underline | not available via API | `__text__` | Renders as bold |
| Code (inline) | `` `code` `` | | |
| Code block | 4-space indentation | ` ``` ` (triple backticks) | Triple backticks break the MCP tool |
| Quote | `> text` | | |
| Bullet list | `•` (Unicode bullet char) | `- item` | Hyphen renders as a literal dash |
| Numbered list | `1. item` | | |
| Link | `<url\|display text>` | `[text](url)` | Standard markdown links don't render |
| User mention | `<@USER_ID>` | `@name` | |
| Channel mention | `<#CHANNEL_ID>` | `#channel` | |
| Emoji | `:emoji_name:` | | e.g. `:wave:`, `:rocket:` |
| Headers | not supported in messages | `##`, `###` | Use `**bold**` for section labels |
| Nested lists | not supported | | Renders flat regardless of indent |

The Unicode bullet (`•`) is banned in customer-facing prose everywhere else; Slack is the carve-out, because the API requires it.

## Length tiers

Slack messages are shorter than email. Keep within these caps:

| Message type | Max words | Notes |
|--------------|-----------|-------|
| Thread reply (Tier 1) | 20 | Ultra-short. Match energy. |
| Thread reply (Tier 2) | 50 | Brief but complete. |
| DM (Tier 1) | 30 | Quick acknowledgment or status. |
| DM (Tier 2) | 80 | Room for context, stay concise. |
| Channel post | 100 | Structured. Bullets for clarity if enumerated. |
| Hard ceiling | 5,000 chars | Slack API limit. Split if exceeded. |

Tier 1 is acknowledgments, status, quick reactions. Tier 2 is anything that needs context.

## Greeting and closing

**Thread reply:** no greeting, no closing. The thread is the context.
