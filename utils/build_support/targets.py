#===--------------------------- targets.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the build target helpers.
"""


import platform


class Platform(object):
    """
    Representation of a platform Unsung Anthem can run on.
    """

    def __init__(self, name, system, archs):
        """
        Create a platform with the given name and list of architectures.

        self -- this object.
        name -- the name of the platform for the user to see.
        system -- the name of the system of the platform for the comparisons.
        archs -- the possible architectures for this platform.
        """
        self.name = name
        self.system = system
        self.targets = [Target(self, arch) for arch in archs]

        # Add a property for each arch.
        for target in self.targets:
            setattr(self, target.arch, target)

    def contains(self, target_name):
        """
        Check whether the given target name belongs to one of the targets of
        this platform.

        self -- this object.
        target_name -- the name of the target to check.
        """
        for target in self.targets:
            if target.name == target_name:
                return True
        return False


class Target(object):
    """
    Representation of a target Unsung Anthem can run on.
    """

    def __init__(self, system, arch):
        self.platform = system
        self.arch = arch

    @property
    def name(self):
        return "{}-{}".format(self.platform.name, self.arch)


def host_target():
    """
    Return the host target for the build machine, if it is one of
    the recognized targets. Otherwise, throw a NotImplementedError.
    """
    system = platform.system()
    machine = platform.machine()

    def _impl_filter_armv(target):
        if system == "Linux":
            return (machine.startswith("armv6") and target == "armv6") \
                or (machine.startswith("armv7") and target == "armv7")

        return False

    macos = Platform("macos", "Darwin", archs=["x86_64"])

    linux = Platform("linux", "Linux", archs=["x86_64",
                                              "armv6",
                                              "armv7",
                                              "aarch64",
                                              "powerpc64",
                                              "powerpc64le",
                                              "s390x"])

    freebsd = Platform("freebsd", "FreeBSD", archs=["x86_64"])

    cygwin = Platform("cygwin", "CYGWIN_NT-10.0", archs=["x86_64"])

    windows = Platform("windows", "Windows", archs=["x86_64"])

    # The list of known platforms.
    known_platforms = [macos, linux, freebsd, cygwin, windows]

    found_platform = [p for p in known_platforms if p.system == system]

    if found_platform:
        found_target = [t for t in found_platform[0].targets
                        if t.arch == machine or _impl_filter_armv(t)]

        if found_target:
            return found_target[0]

    raise NotImplementedError("System \"{}\" with architecture \"{}\" is not "
                              "supported".format(system, machine))
