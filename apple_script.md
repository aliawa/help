# Vocubulary

assignment statement:
    A statement that assigns a value to a variable

expression: 
    Any series of lexical elements that have a value

evaluation:
    The process of converting expressions into values



# target
A tell statement specifies a default target for all commands

tell application "Finder"
    get name of first window
end tell


tell last file of window 1 of application "Finder"
    duplicate
end tell


# Working examples
tell application "Wireshark"
    activate
end tell

tell application "Wireshark"
    it
end tell

tell application "System Events"
	tell process "Wireshark"
		-- Perform user interface scripting tasks
		name of every menu of menu bar 1
	end tell
end tell

if application "Wireshark" is running then
	tell application "Wireshark" to activate
	delay 0.5
	tell application "System Events" to ¬
		tell application process "zoom.us"
			keystroke "q" using command down
			delay 0.5
			key code 36
		end tell
end if


# Not working
tell application "Wireshark"
    close
end tell


# Examples
tell application "TextEdit"
    with timeout of 20 seconds
        close document 1 saving ask
    end timeout
end tell

# Application object
frontmost
name 
running

tell application "iTunes" -- doesn't automatically launch app
    if it is running then
        pause
    end if
end tell


if application "iTunes" is running
    tell application "iTunes" to pause
end f


# Useful
run application "TextEdit"
tell application "TextEdit" to run
run myScript --where myScript is a script object

open location "http://www.apple.com"

Bring application to the frontf
activate application "TextEdit"
tell application "TextEdit" to activate
