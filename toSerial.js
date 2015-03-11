autowatch = 1
inlets = 1
outlets = 1

function list(_)
{
	var args = arrayfromargs(arguments)
	var str = args.join(" ") + "\n"
	var bytes = []
	post(str)
	for (var i = 0; i < str.length; ++i)
	{
	    bytes.push(str.charCodeAt(i))
	}
	outlet(0, bytes)
}

function outletComments(num)
{
	assist("input as list of numbers (bytes)")
}

setoutletassist(-1, outletComments)
