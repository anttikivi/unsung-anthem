#===-------------------------- targets.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the build target helpers.
"""


import platform

from .mapping import Mapping


def create_target(system, arch):
    """
    Create a representation of a target that Unsung Anthem can run on.

    system -- the name of the system of the platform for the comparisons.
    arch -- the architecture of this target.
    """
    result = Mapping(
        platform=system,
        arch=arch,
        name="{}-{}".format(system.name, arch)
    )
    return result


def create_platform(name, system, archs):
    """
    Create a representation of a platform that Unsung Anthem can run on.

    name -- the name of the platform.
    system -- the name of the system of the platform for the comparisons.
    archs -- the possible architectures for this platform.
    """
    result = Mapping(name=name, system=system)
    result["targets"] = [create_target(result, arch) for arch in archs]
    for target in result.targets:
        result[target.arch] = target
    return result


def platform_contains(platform_mapping, target_name):
    """
    Check whether the given target name belongs to one of the targets of this
    platform.

    platform_mapping -- the platform object from which to look for the target.
    target_name -- the name of the target to check.
    """
    for target in platform_mapping.targets:
        if target.name == target_name:
            return True
    return False


def host_target():
    """
    Return the host target for the build machine, if it is one of
    the recognized targets. Otherwise, throw a NotImplementedError.
    """
    system = platform.system()
    machine = platform.machine()

    def _filter_armv(target):
        if system == "Linux":
            return (machine.startswith("armv6") and target == "armv6") \
                or (machine.startswith("armv7") and target == "armv7")
        return False

    macos = create_platform(name="macos", system="Darwin", archs=["x86_64"])
    linux = create_platform(
        name="linux", system="Linux", archs=[
            "x86_64",
            "armv6",
            "armv7",
            "aarch64",
            "powerpc64",
            "powerpc64le",
            "s390x"
        ]
    )
    freebsd = create_platform(
        name="freebsd", system="FreeBSD", archs=["x86_64"]
    )
    cygwin = create_platform(
        name="cygwin", system="CYGWIN_NT-10.0", archs=["x86_64"]
    )
    windows = create_platform(
        name="windows", system="Windows", archs=["x86_64", "AMD64"]
    )
    known_platforms = [macos, linux, freebsd, cygwin, windows]
    found_platform = [p for p in known_platforms if p.system == system]
    if found_platform:
        found_target = [t for t in found_platform[0].targets
                        if t.arch == machine or _filter_armv(t)]
        if found_target:
            return found_target[0]
    raise NotImplementedError(
        "System '{}' with architecture '{}' is not supported".format(
            system, machine
        )
    )
