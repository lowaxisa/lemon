# Isso cria um runner pra cpus antigas

# Boot
# Variaveis
# Check de diretorios
# Compilar
# Montagem

# BOOT
Write-Host "Generic CPU builder"

# VARIAVEIS
$vcvars_dir = "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
$curr_dir   = $PSScriptRoot
$root_dir   = ($curr_dir + "\..")
$build_dir  = ($root_dir + "\build\llama")
$target_dir = ($root_dir + "\tests\backends\generic-cpu")
$flags      = @(
    "-DBUILD_SHARED_LIBS=ON",
    "-DLLAMA_BUILD_TOOLS=ON   -DLLAMA_BUILD_SERVER=ON",
    "-DLLAMA_BUILD_APP=OFF    -DLLAMA_BUILD_TESTS=OFF   -DLLAMA_BUILD_EXAMPLES=OFF",
    "-DLLAMA_OPENSSL=OFF",
    "-DGGML_NATIVE=OFF",
    "-DGGML_SSE42=ON   -DGGML_AVX=ON",
    "-DGGML_AVX2=OFF   -DGGML_BMI2=OFF   -DGGML_AVX512=OFF   -DGGML_AVX_VNNI=OFF",
    "-DGGML_LTO=ON"
)

# CHECAR DIRETORIOS
if (-not (Test-Path -Path $build_dir)) {
    # o  > $null silencia a saida
    New-Item -ItemType Directory -Path $build_dir > $null
    Write-Host "[ + ] Created build dir"
}
if (-not (Test-Path -Path $target_dir)) {
    New-Item -ItemType Directory -Path $target_dir > $null
    Write-Host "[ + ] Created target dir"
}

# COMPILAR
$compile_cmd = "cmake " + $flags + " -S " + ($root_dir + "\thirdparty\llama") + " -B $build_dir -G `"Visual Studio 18 2026`" -A x64 && cmake --build $build_dir --config Release"
& cmd.exe /c "call `"$vcvars_dir`" && $compile_cmd"

# MONTAGEM
Copy-Item ($build_dir + "\bin\Release\*.dll") $target_dir
Copy-Item ($build_dir + "\bin\Release\llama-server.exe") $target_dir
Write-Host "[ + ] generic-cpu runner finished"