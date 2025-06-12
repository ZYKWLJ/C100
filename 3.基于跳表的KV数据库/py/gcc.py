import os
import subprocess
import sys
import time
import re

# 配置部分
COMPILER = "gcc"
CFLAGS = ["-Wall", "-Wextra", "-O2", "-MMD"]  # 简化配置
SOURCE_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "src")  # 修改为正确的源文件路径
BUILD_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "build")
BIN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "bin")
EXECUTABLE = "hd"

def ensure_dirs():
    """确保所有需要的目录存在"""
    os.makedirs(BUILD_DIR, exist_ok=True)
    os.makedirs(BIN_DIR, exist_ok=True)

def get_source_files():
    """获取所有源文件（返回绝对路径）"""
    source_files = []
    if os.path.exists(SOURCE_DIR):
        for root, _, files in os.walk(SOURCE_DIR):
            for file in files:
                if file.endswith(".c"):
                    source_files.append(os.path.abspath(os.path.join(root, file)))
    else:
        print(f"Warning: Source directory not found: {SOURCE_DIR}")
    return source_files

def compile_project():
    """主编译流程"""
    start_time = time.time()
    ensure_dirs()
    
    # 获取源文件
    source_files = get_source_files()
    if not source_files:
        print("Error: No source files found in", SOURCE_DIR)
        return False
    
    object_files = []
    compiled_count = 0
    success = True
    
    # 编译每个源文件
    for src_file in source_files:
        # 生成目标文件路径（保持src目录结构）
        rel_path = os.path.relpath(src_file, SOURCE_DIR)
        obj_file = os.path.join(BUILD_DIR, os.path.splitext(rel_path)[0] + ".o")
        os.makedirs(os.path.dirname(obj_file), exist_ok=True)
        
        # 总是重新编译（简化逻辑）
        print(f"[CC] {rel_path}")
        cmd = [COMPILER] + CFLAGS + ["-c", src_file, "-o", obj_file]
        
        try:
            subprocess.run(cmd, check=True)
            compiled_count += 1
            object_files.append(obj_file)
        except subprocess.CalledProcessError as e:
            print(f"Error compiling {rel_path}")
            success = False
            break
    
    # 如果编译成功则进行链接
    if success and object_files:
        executable_path = os.path.join(BIN_DIR, EXECUTABLE)
        os.makedirs(BIN_DIR, exist_ok=True)
        
        print("\n[LD] Linking executable...")
        cmd = [COMPILER] + object_files + ["-o", executable_path]
        try:
            subprocess.run(cmd, check=True)
            print(f"\nCreated executable: {os.path.relpath(executable_path, os.getcwd())}")
        except subprocess.CalledProcessError as e:
            print("\nLinking failed:")
            success = False
    
    # 输出统计信息
    total_time = time.time() - start_time
    print("\nCompilation summary:")
    print(f"  Total files:    {len(source_files)}")
    print(f"  Compiled:       {compiled_count}")
    print(f"  Time elapsed:   {total_time:.2f} seconds")
    print(f"  Build status:   {'SUCCESS' if success else 'FAILED'}")
    
    return success

def run_executable():
    """运行生成的可执行文件"""
    executable_path = os.path.join(BIN_DIR, EXECUTABLE)
    if sys.platform == "win32":
        executable_path += ".exe"
    
    if os.path.exists(executable_path):
        print(f"\nRunning executable: {executable_path}")
        try:
            subprocess.run([executable_path], check=True)
        except subprocess.CalledProcessError as e:
            print(f"Error running executable: {e}")
    else:
        print(f"Error: Executable not found at {executable_path}")

if __name__ == "__main__":
    if sys.platform == "win32":
        os.system("color")
    
    if compile_project():
        run_executable()
    else:
        sys.exit(1)