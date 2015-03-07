autowatch = 1
outlets = 6

function b() //button
{
	var args = arrayfromargs(arguments)
	var buttonNum = args[0]
	var pressed = args[1]
		
	if (buttonNum < 3) {
		outlet(buttonNum, pressed)
	} else if (buttonNum >= 8) {
		 
    } else if (pressed) {
		outlet(3, buttonNum - 1)
	}
}

function p() //(soft)pot
{
	var args = arrayfromargs(arguments)
	var potNum = args[0]
	var valStr = args.slice(1,args.length).join("")
	var value = Number(valStr) / 1024.0

	outlet(4 + potNum, value)
}

function outletComments(num)
{
	assist(num == 0 ? "layering button?"
         : num == 1 ? "freeze button"
         : num == 2 ? "store button"
         : num == 3 ? "preset recall buttons"
         : ("softpot " + (num-3) + " value"))
}

setoutletassist(-1, outletComments)
