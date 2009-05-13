var list_across0 = [
'_contents_xml.htm',
'_reference.xml',
'_index.xml',
'_search_xml.htm',
'_external.xml'
];
var list_up0 = [
'cppad.xml',
'op.xml',
'revasinop.xml'
];
var list_down2 = [
'distribute.xml',
'newfeature.xml',
'define.xml',
'greaterthanzero.xml',
'greaterthanorzero.xml',
'lessthanzero.xml',
'lessthanorzero.xml',
'identicalpar.xml',
'identicalzero.xml',
'identicalone.xml',
'identicalequalpar.xml',
'opcode.xml',
'printop.xml',
'numind.xml',
'numvar.xml',
'tape_link.xml',
'recorder.xml',
'player.xml',
'adtape.xml',
'boolfunlink.xml',
'op.xml',
'forward_sweep.xml',
'reversesweep.xml',
'forjacsweep.xml',
'revjacsweep.xml'
];
var list_down1 = [
'forabsop.xml',
'revabsop.xml',
'foraddop.xml',
'revaddop.xml',
'foracosop.xml',
'revacosop.xml',
'forasinop.xml',
'revasinop.xml',
'foratanop.xml',
'revatanop.xml',
'fordivvvop.xml',
'revdivvvop.xml',
'forexpop.xml',
'revexpop.xml',
'forlogop.xml',
'revlogop.xml',
'formulvvop.xml',
'revmulvvop.xml',
'forsincos.xml',
'revsincos.xml',
'forsqrtop.xml',
'revsqrtop.xml',
'forsubvvop.xml',
'revsubvvop.xml'
];
var list_current0 = [
'revasinop.xml#Syntax',
'revasinop.xml#Description',
'revasinop.xml#x',
'revasinop.xml#z',
'revasinop.xml#b',
'revasinop.xml#On Input',
'revasinop.xml#On Input.px',
'revasinop.xml#On Input.pz',
'revasinop.xml#On Input.pb',
'revasinop.xml#On Output',
'revasinop.xml#On Output.px',
'revasinop.xml#On Output.pz',
'revasinop.xml#On Output.pb'
];
function choose_across0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_across0[index-1];
}
function choose_up0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_up0[index-1];
}
function choose_down2(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down2[index-1];
}
function choose_down1(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down1[index-1];
}
function choose_down0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down0[index-1];
}
function choose_current0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_current0[index-1];
}