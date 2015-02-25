autowatch = 1
outlets = 3

function b() //button
{
	var args = arrayfromargs(arguments)
	var buttonNum = args[0]
	var pressed = args[1]
	
	buttonNum -= 3 // temporary
	
	if (buttonNum < 2) {
		outlet(buttonNum, pressed)
	} else if (pressed) {
		outlet(2, buttonNum - 1)
	}
}

function outletComments(num)
{
	assist(num == 0 ? "freeze button"
         : num == 1 ? "store button"
         : "preset recall buttons")
}

setoutletassist(-1, outletComments)
