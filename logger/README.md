# Logger

This is a lightweight raw data logger for arduino, combined with a
parser for a computer. These can be switched, since the only
difference is how input and output are obtained and that is determined
at compile time. The design of the protocol is given below.

## Protocol

The logger message protocol has a fairly straightforward design.

| Start | Log Level | Subsystem | Msg Type | Len | Payload |
|-------|-----------|-----------|----------|-----|---------|
| '>'   | 1 byte id | 1 byte id | 1 byte id | # of bytes in payload | {Len} byte payload specified by previous field |

### Payload

The content of the payload depends on the type of the message. There
are several builtin types for the parser, along with a generic format
for all other types.

The builtin types are:
* Time
* Count
* Version
* Print

And the generic type is referred to as:
* Raw Data

The format of the payloads of these types is given below.

#### Time

| Type of time measurement | 4 byte time measurement | Unknown length string |
| --- | --- | --- |
| 'b'/'e' | in microseconds | id |

#### Count

| 4 byte unsigned int | Unknown length string |
| --- | --- |
| count | id, no null-terminating character |

#### Version

| 1 byte major | 1 byte minor | 1 byte build |
| --- | --- | --- |


#### Print

| Unknown length string |
| --- |
| no null-terminating character |

#### Raw Data

| 1 byte length of data | data | string id |
| --- | --- | --- |
| to know how large data is | raw data | used for variable identification, type identification should be in message type|
