cmake_minimum_required(VERSION 3.5)

project(ModernC LANGUAGES C)

add_executable(ModernC
	oopcore.h
	IEntity.h
	IHuman.h
	IRunable.h
	Girl.h Girl.c
	UberGirl.h UberGirl.c
	main.c
)
