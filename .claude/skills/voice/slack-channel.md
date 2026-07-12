# Slack Channel Mechanics

Slack format constraints layered on the base voice rules: MCP-tool markdown quirks, message length tiers, channel-specific greeting/closing carve-outs. Apply when sending or drafting any Slack message via the Slack MCP tool.

## Slack markdown via the MCP tool

The MCP Slack tool accepts **standard markdown** and converts it to Slack's native format. This is **different** from Slack's own mrkdwn syntax. The conversions are non-negotiable; getting them wrong produces broken or literal-rendered messages.

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

**Bullet character carve-out:** `brand-voice.md` bans the Unicode bullet (`•`) in customer-facing prose. Slack reverses that: the API requires `•` for proper bullet rendering. This per-channel exception is allowed.

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

## Greeting and closing rules (channel-specific)

Greetings/closings per Slack message type live in `personal-voice.md` (greetings table + channel calibration matrix). Slack-only patterns to remember:

- **DM, continuing same-day exchange:** skip the greeting, jump straight in. The user's pattern: *"So."* or directly into the topic.
- **Thread reply:** no greeting, no closing. The thread is the context.

## Pre-send checklist (Slack-specific format)

Run before sending. Voice/brand checklists from `personal-voice.md` and `brand-voice.md` still apply.

- [ ] `**bold**` (double asterisks), not `*bold*`
- [ ] `•` for bullets, not `-`
- [ ] 4-space indent for code blocks, not triple backticks
- [ ] No `##` or `###` headers
- [ ] Links use `<url|display>` syntax, not `[text](url)`
- [ ] User/channel mentions use `<@USER_ID>` / `<#CHANNEL_ID>`
- [ ] Within length tier for the message type
- [ ] Under 5,000 character API limit
- [ ] Thread replies have no greeting/closing
