<!-- ---------------------------------------------------------------------- -->
<!--                                                                        -->
<!-- This file is part of Sublime Code.                                     -->
<!--                                                                        -->
<!-- Sublime Code is free software: you can redistribute it and/or modify   -->
<!-- it under the terms of the GNU General Public License as published by   -->
<!-- the Free Software Foundation, either version 3 of the License, or      -->
<!-- (at your option) any later version.                                    -->
<!--                                                                        -->
<!-- Sublime Code is distributed in the hope that it will be useful,        -->
<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of         -->
<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          -->
<!-- GNU General Public License for more details.                           -->
<!--                                                                        -->
<!-- You should have received a copy of the GNU General Public License      -->
<!-- along with Sublime Code.  If not, see <http://www.gnu.org/licenses/>.  -->
<!--                                                                        -->
<!-- ---------------------------------------------------------------------- -->

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
		<xsl:for-each select="MyRowTiTi">
			<table border='2' CELLSPACING='0' CELLPADDING='8' >
			<thead><TH>NAME</TH><TH>ID</TH></thead>
			<tbody>
			<xsl:for-each select="MyRowToTo">
				<TR>
					<TD><xsl:value-of select="Name"/></TD>
					<TD><xsl:value-of select="ID"/></TD>
				</TR>
			</xsl:for-each>
			</tbody>
			</table>
		</xsl:for-each>  
	</body>
	</html>
	</xsl:template>
</xsl:stylesheet>
