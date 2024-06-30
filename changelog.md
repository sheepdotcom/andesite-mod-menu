# v0.0.1-alpha.14

- Update to Geode v3.1.1 for 2.206
- Copy Hack has been added (currently broken)
- New section

# v0.0.1-alpha.13

- Fixed the touch priority on the vanilla options menu and the hack info menu.
- Updated `about.md`.

# v0.0.1-alpha.12

- Made the placeholder text for input hacks no longer extend outside the input zone.
- Text Character Bypass hacks should no longer work inside of input hacks.
- Added a small label and a suffix label to input hacks, just like MegaHack Mobile has.
- More customizability for creating input hacks.
- Most likely fixed an issue where the hack menu would sometimes take priority over the hack options menu.
- Added a dropdown hack that lets you select from any preset values.
- The hack options menu will now darken the background a little bit just like the hacks menu.
- The hack menu has a much higher z order so now it should go on top of other buttons.
- There are currently touch priority issues causing the vanilla options menu and the hack info menu to be unusable while the main hack menu was open.

# v0.0.1-alpha.11

- Fixed an issue where the Hack Options Menu would extend more than it should when it had an even number of options.
- Made some changes to `changelog.md` including making some changes more understandable.
- Changed the texture of the section buttons to not look the same as the hack buttons.
- Added a custom input hack that is currently unfinished.
- Updated `about.md` and `README.md`.

# v0.0.1-alpha.10

- Added a menu to swap between sections, though this is very unfinished.

# v0.0.1-alpha.9

- The text inside the options menu will no longer extend outside the popup.
- The options button inside the hack menu now goes straight to the more options layer rather than the generic options layer.
- Fixed the position of the close button in the hack options menu.
- Having more than 2 options in the hack options menu will now scale the menu to fit the extra options.
- The escape button now closes both the hack menu and the hack options menu.

# v0.0.1-alpha.8

- Hacks can now have options with in them for more customizablility.
- The hack options menu is very similar to MegaHack Mobile but still needs a lot of fixes and some missing features to be added.
- Changed the hacks menu from `FLAlertLayer` to `CCLayerColor`, changed multiple variable names, and renamed many files.

# v0.0.1-alpha.7

- Made the positioning and scale of the hack buttons and info buttons more accurate to MegaHack Mobile.
- Added a third test button.

# v0.0.1-alpha.6

- Added an entire system for storing and creating hacks (This took a lot of effort).
- Made the hack name labels on the buttons smaller.
- Having multiple hacks now works properly.
- Added info buttons that display details on what each hack does.
- Hacks will now save what state they are in.

# v0.0.1-alpha.5

- Changed the mod ID from `andesite` to `andesite-hacks`.
- Added the mod's repository link to `mod.json`.
- Updated `changelog.md` to look better and updated `about.md`.

# v0.0.1-alpha.4

- Made the hack menu slightly wider.
- Added a settings button to the hack menu.
- Internal code changes allowing for custom width and height of the hacks menu if needed.

# v0.0.1-alpha.3

- Made the toggle buttons look more like MegaHack Mobile rather than being default, but still needs scaling and positioning adjustments.
- Added more IDs to objects in the menu layer.

# v0.0.1-alpha.2

- Fixed Hack Buttons not working.
- Disabled the broken copy hack.
- Added title text to the menu.

# v0.0.1-alpha.1

- First alpha build release, menu is working but nothing is in it yet.