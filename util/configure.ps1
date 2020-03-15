#!/usr/bin/env pwsh

# ---------------------------------------------------------------------------- #
#                         Obliging Ode & Unsung Anthem
# ---------------------------------------------------------------------------- #
#
# This source file is part of the Obliging Ode and Unsung Anthem projects.
#
# Copyright (c) 2020 Antti Kivi
# All rights reserved
#
# ---------------------------------------------------------------------------- #

New-Variable ComposerName "Couplet Composer" -Option Constant
New-Variable OdeName "Obliging Ode" -Option Constant
New-Variable AnthemName "Unsung Anthem" -Option Constant

Write-Output "Running the PowerShell wrapper for $ComposerName, the build script of $OdeName and $AnthemName"
Write-Output "$ComposerName will be run in configuring mode"

New-Variable PresetModeArgument "preset" -Option Constant
New-Variable ConfigureModeArgument "configure" -Option Constant

New-Variable ComposerExecutableName "couplet-composer" -Option Constant

# Set up Couplet Composer

New-Variable SetUpPath (Join-Path $PSScriptRoot "set_up") -Option Constant

Write-Output "Going to run the set-up script for $ComposerName from $SetUpPath"

& $SetUpPath $args

Write-Output "The set-up script for $ComposerName has finished"

# Run the script

$Arguments = ""

if ($PresetModeArgument -in $args) {
  $ArgumentsList = $args + $ConfigureModeArgument
  $ArgumentsList = ,$ComposerExecutableName + $ArgumentsList
  $ArgumentsList = ,"run" + $ArgumentsList
  $Arguments = [string]($ArgumentsList)
} else {
  $ArgumentsList = @($ConfigureModeArgument) + $args
  $ArgumentsList = ,$ComposerExecutableName + $ArgumentsList
  $ArgumentsList = ,"run" + $ArgumentsList
  $Arguments = [string]($ArgumentsList)
}

$ProcessStartInfo = New-Object System.Diagnostics.ProcessStartInfo
$ProcessStartInfo.CreateNoWindow = $true
$ProcessStartInfo.FileName = "pipenv"
$ProcessStartInfo.Arguments = $Arguments
$ProcessStartInfo.UseShellExecute = $false
$ProcessStartInfo.RedirectStandardError = $true
$ProcessStartInfo.RedirectStandardOutput = $true

Write-Output "$ComposerName will be run with the command ${ProcessStartInfo.File} ${ProcessStartInfo.Arguments}"

$Process = New-Object System.Diagnostics.Process
$Process.StartInfo = $ProcessStartInfo

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

exit $Process.ExitCode
