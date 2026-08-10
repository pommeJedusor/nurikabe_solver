const game = document.getElementById("game");
const squares = game.children[0].children;
const size = Math.sqrt(squares.length);
let result = "";
let y;
let x;
let square;
y = 0;
while (y < size)
{
	x = 0;
	while (x < size)
	{
		square = squares[y * size + x].textContent;
		if (square == "")
			square = "_";
		else
			square = String.fromCharCode(parseInt(square) + "0".charCodeAt(0));
		result += square;
		x++;
	}
	result += "\n";
	y++;
}
result = prompt(result).replace(/ /g, "");
console.log(result);
y = 0;
while (y < size)
{
	x = 0;
	while (x < size)
	{
		if (result[y * size + x] == "~")
		{
			Game.setCellState({row: y, col: x}, 1);
		}
		x++;
	}
	y++;
}
