<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/SearchByType">
	<html>
	<head>
		<meta http-equiv='Content-Type' content='text/html; charset=iso-8859-1' />
	</head>
	<body>
		<h1>Search for <xsl:value-of select="target"/></h1>
			<table border='2' CELLSPACING='0' CELLPADDING='8' >
			<thead><TH>Number</TH><TH>Line</TH><TH>Path</TH><TH>Name</TH></thead>
			<tbody>
			<xsl:for-each select="Type">
				<TR>
					<TD><xsl:value-of select="Number"/></TD>
					<TD><xsl:value-of select="Line"/></TD>
					<TD><a>
						<xsl:attribute name="href">Path///<xsl:value-of select="Number"/></xsl:attribute>
						<xsl:value-of select="Path"/>
					</a></TD>
					<TD><xsl:value-of select="Name"/></TD>
				</TR>
			</xsl:for-each>
			</tbody>
			</table>
	</body>
	</html>
	</xsl:template>
</xsl:stylesheet>
