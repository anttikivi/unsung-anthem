# anthem_build_support/targets.py - Build target helpers ---------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

import os
import platform


class Platform(object):
    """
    Abstract representation of a platform Unsung Anthem can run on.
    """

    def __init__(self, name, archs):
        """
        Create a platform with the given name and list of architectures.
        """
        self.name = name
        self.targets = [Target(self, arch) for arch in archs]

        # Add a property for each arch.
        for target in self.targets:
            setattr(self, target.arch, target)

    @property
    def is_darwin(self):
        """Convenience function for checking if this is a Darwin platform."""
        return isinstance(self, DarwinPlatform)

    @property
    def supports_benchmark(self):
        # By default, benchmarks are not supported on most platforms.
        return False

    def contains(self, target_name):
        """
        Returns True if the given target name belongs to one of the targets of
        this platform.
        """
        for target in self.targets:
            if target.name == target_name:
                return True
        return False


class DarwinPlatform(Platform):
    def __init__(self, name, archs):
        super(DarwinPlatform, self).__init__(name, archs)

    @property
    def is_embedded(self):
        """Check if this is a Darwin platform for embedded devices."""
        return self.name != 'macos'

    @property
    def supports_benchmark(self):
        # By default, on Darwin benchmarks are supported as the Darwin
        # platforms are not simulations.
        return True


class Target(object):
    """
    Abstract representation of a target Unsung Anthem can run on.
    """

    def __init__(self, platform, arch):
        self.platform = platform
        self.arch = arch
        # Delegate to the platform, this is usually not arch specific.
        self.supports_benchmark = self.platform.supports_benchmark

    @property
    def name(self):
        return '{}-{}'.format(self.platform.name, self.arch)


class DeploymentTarget(object):
    macOS = DarwinPlatform('macos', archs=['x86_64'])

    Linux = Platform('linux', archs=['x86_64',
                                     'armv6',
                                     'armv7',
                                     'aarch64',
                                     'powerpc64',
                                     'powerpc64le',
                                     's390x'])

    FreeBSD = Platform('freebsd', archs=['x86_64'])

    Cygwin = Platform('cygwin', archs=['x86_64'])

    Windows = Platform('windows', archs=['x86_64'])

    # The list of known platforms.
    known_platforms = [macOS, Linux, FreeBSD, Cygwin, Windows]

    # Cache of targets by name.
    _targets_by_name = dict((target.name, target)
                            for platform in known_platforms
                            for target in platform.targets)

    @staticmethod
    def host_target():
        """
        Return the host target for the build machine, if it is one of
        the recognized targets. Otherwise, throw a NotImplementedError.
        """
        system = platform.system()
        machine = platform.machine()

        if system == 'Linux':
            if machine == 'x86_64':
                return DeploymentTarget.Linux.x86_64

            elif machine.startswith('armv7'):
                # linux-armv7* is canonicalized to 'linux-armv7'
                return DeploymentTarget.Linux.armv7

            elif machine.startswith('armv6'):
                # linux-armv6* is canonicalized to 'linux-armv6'
                return DeploymentTarget.Linux.armv6

            elif machine == 'aarch64':
                return DeploymentTarget.Linux.aarch64

            elif machine == 'ppc64':
                return DeploymentTarget.Linux.powerpc64

            elif machine == 'ppc64le':
                return DeploymentTarget.Linux.powerpc64le

            elif machine == 's390x':
                return DeploymentTarget.Linux.s390x

        elif system == 'Darwin':
            if machine == 'x86_64':
                return DeploymentTarget.macOS.x86_64

        elif system == 'FreeBSD':
            if machine == 'amd64':
                return DeploymentTarget.FreeBSD.x86_64

        elif system == 'CYGWIN_NT-10.0':
            if machine == 'x86_64':
                return DeploymentTarget.Cygwin.x86_64

        elif system == 'Windows':
            if machine == "AMD64":
                return DeploymentTarget.Windows.x86_64

        raise NotImplementedError('System "%s" with architecture "%s" is not '
                                  'supported' % (system, machine))

    @staticmethod
    def default_deployment_targets():
        """
        Return targets for the Unsung Anthem stdlib, based on the build
        machine.
        If the build machine is not one of the recognized ones, return None.
        """

        host_target = DeploymentTarget.host_target()

        if host_target is None:
            return None

        # All other machines only configure them by default.
        return [host_target]

    @classmethod
    def get_target_for_name(cls, name):
        return cls._targets_by_name.get(name)


def install_prefix():
    """
    Returns the default path at which built Unsung Anthem products (like bin,
    lib, and include) will be installed, based on the host machine's operating
    system.
    """
    # TODO Add Windows
    if platform.system() == 'Darwin':
        return '/Applications/Xcode.app/Contents/Developer/Toolchains/' + \
               'XcodeDefault.xctoolchain/usr'
    else:
        return '/usr'


def darwin_toolchain_prefix(darwin_install_prefix):
    """
    Given the install prefix for a Darwin system, and assuming that that path
    is to a .xctoolchain directory, return the path to the .xctoolchain
    directory.
    """
    return os.path.split(darwin_install_prefix)[0]
