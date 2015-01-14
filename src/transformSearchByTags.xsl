<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">  
	<html>
	<head>
		<title>Unitary test report</title>
		<meta http-equiv='Content-Type' content='text/html; charset=iso-8859-1' />
	</head>
	<body>
		<h1>WESHHH XML Transform</h1>
		<xsl:for-each select="SearchByTags">
			<table border='2' CELLSPACING='0' CELLPADDING='8' >
			<thead><TH>Number</TH><TH>Line</TH><TH>Path</TH><TH>Type</TH></thead>
			<tbody>
			<xsl:for-each select="Tags">
				<TR>
					<TD><xsl:value-of select="Number"/></TD>
					<TD><xsl:value-of select="Line"/></TD>
					<TD><xsl:value-of select="Path"/></TD>
					<TD><xsl:value-of select="Type"/></TD>
				</TR>
			</xsl:for-each>
			</tbody>
			</table>
		</xsl:for-each>  
	</body>
	</html>
	</xsl:template>
</xsl:stylesheet>
