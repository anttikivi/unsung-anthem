#!/usr/bin/env pwsh

# ---------------------------------------------------------------------------- #
#                         Obliging Ode & Unsung Anthem
# ---------------------------------------------------------------------------- #
#
# This source file is part of the Obliging Ode and Unsung Anthem projects.
#
# Copyright (c) 2019 Antti Kivi
# All rights reserved
#
# ---------------------------------------------------------------------------- #

New-Variable ComposerVersion "0.5.3" -Option Constant
New-Variable ComposerName "Couplet Composer" -Option Constant
New-Variable OdeName "Obliging Ode" -Option Constant
New-Variable AnthemName "Unsung Anthem" -Option Constant

Write-Output "Running the PowerShell wrapper for $ComposerName $ComposerVersion, the build script of $OdeName and $AnthemName"
Write-Output "$ComposerName will be run in composing mode"

New-Variable RootDir "." -Option Constant
New-Variable BuildDirName "build" -Option Constant
New-Variable ProjectDirName "unsung-anthem" -Option Constant
New-Variable BuildDir "$RootDir/$BuildDirName" -Option Constant
New-Variable ProjectBuildDir "$RootDir/$ProjectDirName/$BuildDirName" -Option Constant

New-Variable InTreeBuildOption "--in-tree-build" -Option Constant

New-Variable PresetModeArgument "preset" -Option Constant
New-Variable ComposeModeArgument "compose" -Option Constant

New-Variable ComposerExecutableName "couplet-composer" -Option Constant

# See if the directory generated by configuring mode is in place

function Exit-MissingConfiguration {
  Write-Error "The build directory wasn't found; please make sure to run the cofiguring script before attempting to build $OdeName and $AnthemName"
  exit 1
}

if ((-not (Test-Path "$BuildDir")) -and (-not ($InTreeBuildOption -in $args))) {
  Exit-MissingConfiguration
}

if ((-not (Test-Path "$ProjectBuildDir")) -and ($InTreeBuildOption -in $args)) {
  Exit-MissingConfiguration
}

if (-not (Get-Command $ComposerExecutableName -CommandType All -ErrorAction SilentlyContinue)) {
  Exit-MissingConfiguration
}

# Run the script

$ComposerExecutable = (Get-Command $ComposerExecutableName -CommandType All | Select-Object -ExpandProperty Definition)
Write-Output "The installed $ComposerName executable is $ComposerExecutable"

$Arguments = ""

if ($PresetModeArgument -in $args) {
  $Arguments = [string]($args += $ComposeModeArgument)
  Write-Output "Invoking $ComposerExecutable in preset mode with arguments '$Arguments'"
} else {
  $Arguments = [string](@($ComposeModeArgument) + $args)
  Write-Output "Invoking $ComposerExecutable with arguments '$Arguments'"
}

$ProcessStartInfo = New-Object System.Diagnostics.ProcessStartInfo
$ProcessStartInfo.CreateNoWindow = $true
$ProcessStartInfo.FileName = $ComposerExecutable
$ProcessStartInfo.Arguments = $Arguments
$ProcessStartInfo.UseShellExecute = $false
$ProcessStartInfo.RedirectStandardError = $true
$ProcessStartInfo.RedirectStandardOutput = $true

$Process = New-Object System.Diagnostics.Process
$Process.StartInfo = $ProcessStartInfo

# $StandardOutput = New-Object System.Text.StringBuilder
# $StandardError = New-Object System.Text.StringBuilder

# $OutputWaitHandle = New-Object System.Threading.AutoResetEvent -ArgumentList $false
# $ErrorWaitHandle = New-Object System.Threading.AutoResetEvent -ArgumentList $false

$OutputEvent = Register-ObjectEvent -Action {
  Write-Host $Event.SourceEventArgs.Data
} -InputObject $Process -EventName OutputDataReceived

$ErrorEvent = Register-ObjectEvent -Action {
  Write-Host $Event.SourceEventArgs.Data
} -InputObject $Process -EventName ErrorDataReceived

$Process.Start() | Out-Null

$Process.BeginOutputReadLine()
$Process.BeginErrorReadLine()

do {
  Start-Sleep -Seconds 1
} while (-not $Process.HasExited)

$OutputEvent.Name, $ErrorEvent.Name | ForEach-Object {Unregister-Event -SourceIdentifier $_}

# $StandardOutput = $Process.StandardOutput.ReadToEnd()
# $StandardError = $Process.StandardError.ReadToEnd()

# $Process.WaitForExit()

# Write-Host "stdout: $StandardOutput"
# Write-Host "stderr: $StandardError"

exit $Process.ExitCode
