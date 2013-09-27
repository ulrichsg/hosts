Hosts file management tool
==========================

Do you have to edit your /etc/hosts file frequently? Are you tired of it? Then this little utility might be just what you need.
It allows you to add or remove entries from the hosts file with simple console commands.

Installation
------------

No special libraries or runtimes are necessary, just plain old gcc.

```
make
sudo make install
```

Usage
-----

### Commands

There are three commands available:

```
# Add a host named "cthulhu" with the address 1.2.3.4 to the hosts file
hosts add cthulhu 1.2.3.4

# Remove the hosts named "azathoth" and "nyarlathotep" from the hosts file
hosts rm azathoth nyarlathotep

# Print the list of hosts defined in the hosts file
hosts list
```

### Options

The following options can be used either instead of together with a command:

```
# Specify the path to the hosts file (default: /etc/hosts)
hosts add -f /path/to/hosts cthulhu 1.2.3.4

# Print a help screen
hosts -h

# Print version information
hosts -v
```

Caution
-------

If you like having your hosts files cleanly formatted or even commented, you may want to not use this tool after all.
As of now, it removes any comments when it modifies a file and writes it back in a very basic manner.
Only use it if you are fine with that.

