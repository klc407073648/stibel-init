#解决后续cmake文件路径问题
ROOT_PATH=$1
TARGET_FILE_PATH=$2
TMP_FILE_NAME=fun_stat.txt
FILE_NAME=fun_stat.inc

function clear_file()
{
    if [ ! -f ${ROOT_PATH}/cmake/${TMP_FILE_NAME} ];then
        echo "clear ${ROOT_PATH}/cmake/${TMP_FILE_NAME}"
        rm -rf ${ROOT_PATH}/cmake/${TMP_FILE_NAME}
    fi

    if [ ! -f ${ROOT_PATH}/cmake/${FILE_NAME} ];then
        echo "clear ${ROOT_PATH}/cmake/${FILE_NAME}"
        rm -rf ${ROOT_PATH}/cmake/${FILE_NAME}
    fi
}

function search_file_stat()
{
    echo "search file stat"
    cd ${ROOT_PATH}/core
    grep -rn "#define FUN_NAME" | cut -d "#" -f2 | cut -d "\"" -f2 >> ${ROOT_PATH}/cmake/${TMP_FILE_NAME}
}

function write_file()
{
    echo "write file"

    while read -r line
    do
        echo "MAKE_FUN_STAT_ARRAY($line,MAX_ARRAY_NUM)" >> ${ROOT_PATH}/cmake/${FILE_NAME}
    done < ${ROOT_PATH}/cmake/${TMP_FILE_NAME}
}

function copy_file()
{
    echo "cp -rf ${ROOT_PATH}/cmake/${FILE_NAME} ${TARGET_FILE_PATH}"
    cp -rf ${ROOT_PATH}/cmake/${FILE_NAME} ${TARGET_FILE_PATH}
}


function MAIN()
{
    clear_file
    search_file_stat
    write_file
    copy_file
}

MAIN