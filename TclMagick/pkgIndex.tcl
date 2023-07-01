# Hand-written package index file.

package ifneeded TclMagick 0.46 "
[list load [file join $dir TclMagick[info sharedlibextension]]]"

package ifneeded TkMagick 0.46 "
package require Tk
package require TclMagick
[list load [file join $dir TkMagick[info sharedlibextension]]]"
