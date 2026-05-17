param(
    [ValidateSet("Debug", "Release", "RelWithDebInfo")]
    [string]$Config = "Debug",
    [switch]$Clean
)

$ErrorActionPreference = "Stop"

function Find-Ninja {
    $onPath = Get-Command ninja -ErrorAction SilentlyContinue
    if ($onPath) {
        return $onPath.Source
    }

    $vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path $vswhere)) {
        return $null
    }

    $vsInstall = & $vswhere -latest -property installationPath
    if (-not $vsInstall) {
        return $null
    }

    $bundledNinja = Join-Path $vsInstall "Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe"
    if (Test-Path $bundledNinja) {
        return $bundledNinja
    }

    return $null
}

function Enter-VisualStudioDevShell {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path $vswhere)) {
        return $false
    }

    $vsInstall = & $vswhere -latest -property installationPath
    if (-not $vsInstall) {
        return $false
    }

    $devShellModule = Join-Path $vsInstall "Common7\Tools\Microsoft.VisualStudio.DevShell.dll"
    if (-not (Test-Path $devShellModule)) {
        return $false
    }

    Import-Module $devShellModule
    Enter-VsDevShell -VsInstallPath $vsInstall -SkipAutomaticLocation -DevCmdArguments "-arch=amd64"
    return $true
}

$projectRoot = $PSScriptRoot
$buildDir = Join-Path $projectRoot "BuildClangd"
$compileCommands = Join-Path $buildDir "compile_commands.json"
$rootCompileCommands = Join-Path $projectRoot "compile_commands.json"

Set-Location $projectRoot

$ninja = Find-Ninja
if (-not $ninja) {
    Write-Error @"
Ninja was not found. Install one of:
  - Visual Studio workload: Desktop development with C++ (includes CMake/Ninja)
  - winget install Ninja-build.Ninja
Then re-run: .\clangd.ps1
"@
}

if (-not (Enter-VisualStudioDevShell)) {
    Write-Warning "Could not load the Visual Studio dev shell; cmake may fail to find cl.exe."
}

if ($Clean -and (Test-Path $buildDir)) {
    Remove-Item -Recurse -Force $buildDir
}

if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

cmake -S . -B $buildDir -G Ninja `
    -DCMAKE_MAKE_PROGRAM="$ninja" `
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON `
    -DCMAKE_BUILD_TYPE=$Config

if (-not (Test-Path $compileCommands)) {
    Write-Error "compile_commands.json was not generated in $buildDir"
}

Copy-Item -Force $compileCommands $rootCompileCommands

cmake --build $buildDir
if ($LASTEXITCODE -ne 0) {
    Write-Warning "BuildClangd build failed (exit $LASTEXITCODE). compile_commands.json was still updated for clangd."
    Write-Warning "Use .\build.ps1 for your normal Visual Studio build."
}

Write-Host "clangd compile database ready:"
Write-Host "  $compileCommands"
Write-Host "  $rootCompileCommands"
Write-Host ""
Write-Host "Reload the editor or run: clangd: Restart language server"
