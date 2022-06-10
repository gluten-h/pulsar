
# LIB
- [ ] input:
	- [ ] mouse:
		- [ ] add interpolated version of mouse_delta
		- [ ] mouse_button_info is ugly
	- [ ] keyboard:
		- [ ] probably, there is no need of break-codes, input api generates make-codes even when specified flag is RI_KEY_BREAK
- [ ] mesh:
	- [ ] create mesh primitives and write geometry data in constructor directly without messing with files
		- [x] cube
		- [ ] sphere
- [ ] scene:
	- [ ] replace main_camera type with entt::entity
- [ ] dcb:
	- [ ] implement const_layout_elem_ref
	- [ ] implement Array functionality
