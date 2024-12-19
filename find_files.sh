if [ -z "$1" ] || [ -z "$2" ]; then
  echo "пожалуйста, укажите директорию и расширение файлов."
  exit 1
fi

directory=$1
extension=$2

if [ ! -d "$directory" ]; then
  echo "директория не найдена."
  exit 1
fi

found_files=$(find "$directory" -type f -name "*.$extension")


if [ -z "$found_files" ]; then
  echo "файлы с расширением $extension не найдены."
else
  echo "ннеденные файлы с расширением $extension:"
  echo "$found_files"
fi
