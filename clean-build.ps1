param(
    [ValidateSet("Debug", "Release", "RelWithDebInfo")]
    [string]$Config = "Debug"
)

$ErrorActionPreference = "Stop"

if (Test-Path "Build") {
    Remove-Item -Recurse -Force "Build"
}

New-Item -ItemType Directory -Path "Build" | Out-Null

cmake -S . -B Build
cmake --build Build --config $Config