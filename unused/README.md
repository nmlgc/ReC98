This directory only contains *declarations* of unused code for better
discoverability. The implementations have been removed from this branch as

* they just make debloating and porting harder for no reason, and
* we can't ensure that they keep running as debloating and porting continues.

They can still be found on the `master` branch though, where they are needed to
ensure bit-perfect binaries.
