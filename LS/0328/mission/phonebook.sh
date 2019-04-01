#!/bin/bash

touch phonebook

register() {
    clear
    read -p "이름: " name
    if [ ! "$name" ]; then
        echo "이름을 입력하지 않았습니다. 아무 키나 누르세요..."
        read
        return
    fi

    result=$(grep $name phonebook)
    if [ "$result" ]; then
        echo "이미 존재하는 이름입니다. 아무 키나 누르세요..."
        read
        return
    fi

    read -p "전화번호: " tel
    echo "$name  $tel" >> phonebook
    echo "등록되었습니다. 아무 키나 누르세요..."
    read
}

search() {
    clear
    read -p "이름: " name
    if [ ! "$name" ]; then
        echo "이름을 입력하지 않았습니다. 아무 키나 누르세요..."
        read
        return
    fi

    result=$(grep $name phonebook)
    if [ ! "$result" ]; then
        echo "그런 이름은 없습니다. 아무 키나 누르세요..."
        read
        return
    fi

    echo $result
    echo "아무 키나 누르세요..."
    read
}

delete() {
    clear
    read -p "이름: " name
    if [ ! "$name" ]; then
        echo "이름을 입력하지 않았습니다. 아무 키나 누르세요..."
        read
        return
    fi

    result=$(grep $name phonebook)
    if [ ! "$result" ]; then
        echo "그런 이름은 없습니다. 아무 키나 누르세요..."
        read
        return
    fi

    grep -v "$name" phonebook > /tmp/phonebook
    mv /tmp/phonebook phonebook

    echo "삭제되었습니다. 아무 키나 누르세요..."
    read
}

select_menu() {
    clear
    echo "1. 등록"
    echo "2. 검색"
    echo "3. 삭제"
    read -p "입력(0. 종료): "
}

while true; do
    select_menu;

    case $REPLY in
        0) exit 0;;
        1) register;;
        2) search;;
        3) delete;;
        *) echo "잘못 입력하셨습니다. 아무키나 누르세요"; read;;
    esac
done
