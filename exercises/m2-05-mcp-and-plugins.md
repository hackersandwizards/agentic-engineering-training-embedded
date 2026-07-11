# Connect an MCP server

Duration: 30 minutes, after the trainer demo

## Outcome

The agent reaches one external tool through MCP, and the group can state when
a server earns its place in the configuration.

## Task

1. Watch the trainer demo: what MCP is, what a server exposes and what each
   configured server costs in context.
2. Connect one server that serves the training repository, such as the
   provider of your issue tracker, your Git host or a documentation source.
   Use the current official documentation of your coding agent for the
   configuration mechanism.
3. Use the new tools for one concrete task, such as reading an issue or
   querying a document, and compare the result against doing it without MCP.
4. Remove or disable any server whose tools the task did not use.
5. Record the plugin or marketplace mechanism your coding agent offers for
   sharing such configuration across a team. A short note is enough; the
   starter kit collects it on day 2.

The concept is product-neutral: a tool boundary with a schema. The
configuration syntax is the product-specific part, which is why it comes from
current documentation and not from memory.

## Done when

- One MCP-provided tool call succeeded on a real task.
- The configuration contains no server without a named use case.
- The group can say in one sentence what the server may read or change.
