# A ideia eh compilar o exe final pra ser singleton e ai enfiar ele no /tests
# Vo ter que criar um /build e um /tests sempre que isso rodar

# Variaveis
$curr_dir      = $PSScriptRoot
$build_dir     = ($curr_dir + "\build")
$tests_dir     = ($curr_dir + "\tests")
$vcvars_dir    = "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
$exe_build_dir = ($build_dir + "\Release\lemon.exe")
$exe_tests_dir = ($tests_dir + "\lemon.exe")

# Debugprint
Write-Host "> Lemon build system | DIR: $curr_dir"

# Criacao de diretorios se nao existir
if (-not (Test-Path -Path $build_dir)) {
    # o  > $null silencia a saida
    New-Item -ItemType Directory -Path $build_dir > $null
    Write-Host "[ + ] Created build dir"
}
if (-not (Test-Path -Path $tests_dir)) {
    New-Item -ItemType Directory -Path $tests_dir > $null
    Write-Host "[ + ] Created tests dir"
}

Write-Host "[ + ] Compiling Lemon"
$compile_cmd = "cmake -S `"$curr_dir`" -B `"build`" -G `"Visual Studio 18 2026`" -A x64 && cmake --build `"build`" --config Release"
& cmd.exe /c "call `"$vcvars_dir`" && $compile_cmd"

Write-Host "[ + ] Copying lemon.exe into tests"
Copy-Item -Path $exe_build_dir -Destination $tests_dir -Force