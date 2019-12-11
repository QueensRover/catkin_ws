// Serial Write Header

#ifndef SERIALWRITER_H
#define SERIALWRITER_H

class serialWriter {

	public:
		serialWriter();
		void serialSetup(); //setup serial command
		void serialWrite(uint16_t, uint16_t, uint16_t);

	private:
		void open_port(void);
		void configure_port(void);
		int fd;
};

#endif
