macro(print_variable_status var)
		if(${var})
				message(STATUS "Set ${var} : Yes")
		else(${var})
				message(STATUS "Set ${var} : No")
		endif(${var})
endmacro(print_variable_status var)


macro(print_variable_content var)
		message(STATUS "Set ${var} : \"${${var}}\"")
endmacro(print_variable_content var)
