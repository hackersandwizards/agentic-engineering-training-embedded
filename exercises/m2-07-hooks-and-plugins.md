# Observe a hook and package a plugin

Duration: 45 minutes

## Outcome

The group observes one agent lifecycle event and packages a useful artifact so
another developer can activate it without copying files by hand.

## Task

1. Choose one observable event from the day's work: a completed long build, a
   failed verification command or a changed control file.
2. Use current official documentation to add the smallest hook that records the
   event or notifies the developer. Test success and failure.
3. State who can edit the hook and what the hook cannot authorize or secure.
4. Select one skill or custom agent created today. Package it using the plugin
   and marketplace mechanism supported by the group's coding agent.
5. Activate the plugin in a clean session and run its representative task.
6. Record the installation, update and removal path for the team.

## Done when

- A real lifecycle event produces observable output.
- The hook's authority boundary is explicit.
- Another clean session discovers and uses the packaged artifact.
- The repository contains no duplicate source of truth for the packaged content.

