cmake_minimum_required(VERSION 3.5)

project(ModernC LANGUAGES C)

add_executable(ModernC
	oopcore.h
        IAnimal.h IAnimal.c
	Cat.h Cat.c
	Dog.h Dog.c
        main.c
)
