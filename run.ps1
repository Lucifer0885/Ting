param(
    [ValidateSet("Debug", "Release", "RelWithDebInfo")]
    [string]$Config = "Debug"
)

$ErrorActionPreference = "Stop"

$buildDir = Join-Path $PSScriptRoot "Build\$Config"
$exePath = Join-Path $buildDir "ting.exe"

if (-not (Test-Path $buildDir)) {
    Write-Error "Build output not found: $buildDir"
    Exit 1
}

& $exePath